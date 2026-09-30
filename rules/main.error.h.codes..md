# Printing flavoured messages Codes
| Code | For |
| --- | --- |
| 0 | No flavour, empty message with ~ | msg |
| 1 | Note, For remdinding user of something or making a note on something |
| 2 | Tip, For showing tips or potential fix or a better way to do something |
| 3 | Warning, For showing a potential issue or something could go wrong |
# Exception Error Codes
| Code | For |
| --- | --- |
| 0 | Unknown Errors, undocumentaed, or ultra rare cases |
| 1 | When memory allocations malloc() returned null |
| 2 | Read errors, when reading from a file is impossible in anyway |
| 3 | Write errors, when writing to a file is impossible in anyway |
# Lexer Error Codes
| Code | For |
| --- | --- |
| 0 | For unkown error or ultra rare cases, output the last character the Lexical Analyzer was able to read successfully |
| 1 | For detecting starting quote for strings in lexer but does not detect closing quote. |
| 2 | For detecting opening parenthesis but does not detect closing parenthesis. |