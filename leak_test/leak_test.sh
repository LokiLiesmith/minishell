#!/bin/bash
# leak_tests.sh - run minishell under valgrind with common cases

BIN=../bin/minishell
VALGRIND="valgrind --quiet --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=definite"

tests=(
  # PATH search: found & not found
  "ls"
  "idontexist"

  # Absolute path
  "/bin/echo hello"

  # Pipelines
  "echo hi | cat"
  "ls | grep minishell | wc -l"

  # Builtins
  "pwd"
  "export TEST=123"
  "env"
  "unset TEST"
)

echo "==================== Leak Test Results ===================="
for cmd in "${tests[@]}"; do
  echo -e "\n>>> Testing: $cmd"
  echo "$cmd" | $VALGRIND $BIN 2>&1 | grep "definitely lost"
done

# Heredoc test separately with here-doc input
echo -e "\n>>> Testing heredoc"
$VALGRIND $BIN <<EOF 2>&1 | grep "definitely lost"
cat <<END
hello
world
END
EOF

echo "==========================================================="