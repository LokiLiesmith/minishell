#!/bin/bash
# sanity_tests.sh - unified memory + FD leak check for minishell

BIN=./bin/minishell
VALGRIND="valgrind --quiet --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=definite"

tests=(
  "ls"
  "idontexist"
  "/bin/echo hello"
  "echo hi | cat"
  "ls | grep minishell | wc -l"
  "pwd"
  "export TEST=123"
  "env"
  "unset TEST"
)

echo "==================== Memory Leak Test Results ===================="

for cmd in "${tests[@]}"; do
  echo -e "\n>>> Testing: $cmd"
  echo "$cmd" | $VALGRIND $BIN 2>&1 | grep "definitely lost"
done

echo -e "\n>>> Testing heredoc"
$VALGRIND $BIN <<EOF 2>&1 | grep "definitely lost"
cat <<END
foo
bar
END
EOF

echo "=================================================================="

echo -e "\n==================== FD Leak Test Results ===================="

for cmd in "${tests[@]}"; do
  echo -e "\n>>> Testing: $cmd"

  before=$(ls /proc/$$/fd | wc -l)
  echo "$cmd" | $BIN > /dev/null 2>&1
  after=$(ls /proc/$$/fd | wc -l)

  if [ "$before" -eq "$after" ]; then
    echo "FD check: OK ($after FDs open)"
  else
    echo "FD check: POSSIBLE LEAK (before=$before, after=$after)"
  fi
done

echo -e "\n>>> Testing heredoc"
before=$(ls /proc/$$/fd | wc -l)
$BIN <<EOF > /dev/null 2>&1
cat <<END
foo
bar
END
EOF
after=$(ls /proc/$$/fd | wc -l)

if [ "$before" -eq "$after" ]; then
  echo "FD check: OK ($after FDs open)"
else
  echo "FD check: POSSIBLE LEAK (before=$before, after=$after)"
fi

echo "=============================================================="
