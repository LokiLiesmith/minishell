//		echo -n "oh, hi mark" > out.txt < | grep hi >> log.txt
//		_____________________________________			_____________________________________
//		|	t_token_node 0					|			|	t_token_node 1					|
//		|	type = WORD						|			|	type = WORD						|
//		|	string = "echo"					|			|	string = "-n"					|
//		|	quote_single = false			|			|	quote_single = false			|
//		|	quote_double = false			|			|	quote_double = false			|
// 		|	next *    ------------------------------->	|	next *    ------------------------ ...
//		|___________________________________|			|___________________________________|
// 
//		_____________________________________			_____________________________________
//		|	t_token_node 2					|			|	t_token_node 3					|
//		|	type = WORD						|			|	type = R_OUT					|
//		|	string = "oh, hi mark"			|			|	string = ">"					|
//		|	quote_single = false			|			|	quote_single = false			|
//		|	quote_double = TRUE				|			|	quote_double = false			|
//--->	|	next *    ------------------------------->	|	next *    ------------------------ ...
//		|___________________________________|			|___________________________________|
//
//		_____________________________________			_____________________________________
//		|	t_token_node 4					|			|	t_token_node 5					|
//		|	type = WORD						|			|	type = R_IN						|
//		|	string = "out.txt"				|			|	string = "<"					|
//		|	quote_single = false			|			|	quote_single = false			|
//		|	quote_double = false			|			|	quote_double = false			|
//--->	|	next *    ------------------------------->	|	next *    ------------------------ ...
//		|___________________________________|			|___________________________________|
// 														 																												
//		_____________________________________			_____________________________________
//		|	t_token_node 6					|			|	t_token_node 7					|
//		|	type = PIPE						|			|	type = WORD						|
//		|	string = "|"					|			|	string = "grep"					|
//		|	quote_single = false			|			|	quote_single = false			|
//		|	quote_double = false			|			|	quote_double = false			|
//--->	|	next *    ------------------------------->	|	next *    ------------------------ ...
//		|___________________________________|			|___________________________________|
// 														 											