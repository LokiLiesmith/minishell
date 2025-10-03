🔹 1. find_path and search_directories
Change:
Fixed potential memory leaks by freeing intermediate strings (part_path, full_path) properly.
Added fallback to /bin:/usr/bin when PATH is missing.
Made sure only one final allocated string is returned.
Reason:
Valgrind showed reachable/leaked memory when commands failed, because we weren’t freeing unused paths.

🔹 2. execute_cmd and execute_start
Change:
Ensured child processes handle pipes correctly.
Closed pipe FDs in parent (close_pipe_parent).
Integrated prepare_execve to build path and env_array safely with GC.
Reason:
To fix FD leaks and memory leaks during pipeline execution.

🔹 3. env_to_array and GC integration
Change:
Converted env list into an array with gc_malloc and gc_strdup.
Removed double frees by letting GC own all memory.
Reason:
Valgrind was reporting “invalid free” when freeing env strings twice. Using GC removed that risk.

🔹 4. pwd builtin
Change:
Original version leaked memory (getcwd(NULL, 0) result never freed).
Fixed by freeing pwd after printing.
Reason:
Valgrind showed 35 bytes definitely lost. Fixed by cleaning up.

🔹 5. cd builtin
Change:
Implemented with getcwd for OLDPWD and PWD.
Added helpers:
set_env_value(sh, env, key, value) (updates or adds env vars via GC).
get_env_raw(env, key) (safe retrieval).
Error messages match Bash exactly:
HOME not set
OLDPWD not set
print new dir on cd -.
Reason:
Original version double-freed strings (free + gc).
We switched everything to GC-managed env values.

🔹 6. exit builtin
Change:
Handled cases:
exit → exit with last status.
exit N → exit with numeric status (N % 256).
exit abc → “numeric argument required”, exit with 2.
exit 1 2 → “too many arguments”, don’t exit, status 1.
Adjusted function signature and logic to avoid “wrong return type”.
Reason:
Originally printed incorrect errors (sometimes both numeric + too many args). Fixed to match Bash behavior.

🔹 7. echo builtin
Change:
Rewrote logic to handle multiple -n flags (-n, -nnn, etc.).
Correct handling of empty string (echo "") and no args (echo).
Reason:
Original implementation only checked the first arg; failed with multiple -ns.

🔹 8. export builtin
Change:
Implemented proper validation of identifiers.
Splits VAR=value or just VAR.
Uses set_env_value to update or create env vars.
Prints declare -x VAR="value" format when no args.
Reason:
Original version didn’t actually add/update variables. Now matches Bash export rules.

🔹 9. unset builtin
Change:
Changed prototype to builtin_unset(t_cmd *cmd, t_env **env) so head node can be removed.
Fixed unlinking logic (head, middle, tail).
Exact matching with ft_strcmp (no partial matches).
Added identifier validation: invalid → error message.
Reason:
Original version:
Couldn’t remove head node (unset PATH failed).
Used strncmp → unset PA would remove PATH.
Tail removal was fragile.

🔹 10. Testing & Leak Hunting
Change:
Ran builtins manually and with a test script.
Verified with valgrind:
No “definitely lost” memory.
Only GC/Readline “still reachable” blocks remain.
Verified FD leaks: always stable count (no open/forgotten pipes).
Reason:
Ensures minishell passes 42’s memory/FD leak requirements.
✅ Status

All mandatory builtins now behave like Bash:
echo
pwd
cd
export
unset
env
exit
Memory and FD leak checks are clean.
Error messages match Bash closely.