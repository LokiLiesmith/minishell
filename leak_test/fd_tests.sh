#!/bin/bash
# fd_tests.sh - check minishell for open file descriptor leaks

BIN=../bin/minishell

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

echo "==================== FD Leak Test Results ===================="

for cmd in "${tests[@]}"; do
  echo -e "\n>>> Testing: $cmd"

  # Count open FDs before
  before=$(ls /proc/$$/fd | wc -l)

  # Run the command in minishell (quiet)
  echo "$cmd" | $BIN > /dev/null 2>&1

  # Count open FDs after
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
