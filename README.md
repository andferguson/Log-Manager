# C++ Log Manager
## Introduction
In professional software, rather than outputting messages to the standard output stream for the purpose of debugging or indicating errors, developers will typically use log files to hide such information from end-users. Log files are usually quite massive in size and there are often many log entries that may be irrelevant to what the developer is trying to examine. The developer needs to have the ability to quickly search for and analyze only the entries they care about. This project is designed to helps with this task, by creating an interactive manager to search, parse, and edit log files.

## Table of Contents
* [Getting Started](#getting-started)
* [Executable](#executable)
* [Input Format](#input-format)
* [Commands List](#commands-list)
* [Conclusion](#conclusion)

## Getting Started

Compile all files with `make all`

Run on an example log with `logman example-log.txt`

This project also supports input and output redirection.
Run with `logman example-log.txt < example-cmds.txt > example-output.txt`

## Executable
Makefile builds an executable program called `logman`. The program will begin by reading an input file containing log entries, and then will enter an interactive mode where the user can perform  timestamp, category, and  keyword searches for the purpose of constructing an "excerpt list" of the log file.  `logman` also allows the user to manage and display this "excerpt list" to identify the important/relevant entries of their log file.

## Input Format
On startup, `logman`  reads  a series of log entries from the  master log file, a file specified via the command line. The file is a plain text file which describes a single log entry on every line. Each log entry consists of three fields separated by vertical bar (`|`) characters. The first field contains the timestamp of the log entry, the second contains the category of the log entry, and the third contains the message of the log entry. The following is a description of the formats of each field:

* Log  timestamps will be given in the format mm:dd:hh:mm:ss , where the various components (month, day, hour, minute, second) between colons are given as a pair of digits.

* Log  categories will be given as strings and correspond to some general, but meaningful, description of which part of the  logged program outputted the message.

* Log  messages will be given as strings.

An example of two lines from the  master log file:

	10:09:03:45:50|TCP|Packet 0x4235124 sent
	09:15:12:00:00|Clock|Noon 09/15

## Commands List
Search Commands:
  * `t` - timestamp search
    `% t <timestamp1>|<timestamp2>`
    Executes a search for all log  entries with  timestamps that fall within a specified time range and displays the number of matching entries.
  * `m` - matching search
    `% m <timestamp>`
    Searches for all log  entries with  timestamps matching the given timestamp and displays the number of matching  entries.
  * `c` - category search
    `% c <string>`
    Searches for all log  entries with  categories matching  <string>  and displays the number of matching entries.
  * `k` - keyword search
    `% k <string>`
    Perform a  keyword search on the log  categories and log messages, and display the number of matching entries.

Excerpt List Commands:
  * `a` - append log entry  (by entryID)
    `% a <integer>`
    Append the log  entry from position  <integer>  in the  master log file onto  the end of the  excerpt list.
  * `r` - append search results
    `% r`
    Add all log  entries returned by the most recent previous search (commands  t ,  m ,  c , or  k ) to the end of the excerpt list.
  * `d` - delete log entry (by excerpt list number)
    `% d <integer>`
    Remove the  excerpt list  entry at position  <integer>.
  * `b` - move to beginning  (by excerpt list number)
    `% b <integer>`
    Move the  excerpt list  entry at position <  integer> to the beginning of the excerpt list.
  * `e` - move to end  (by excerpt list number)
    `% e <integer>`
    Move the  excerpt list  entry at position <  integer> to the end of the  excerpt list.
  * `s` - sort excerpt list (by timestamp)
    `% s`
    Sort each  entry in the  excerpt list by  timestamp, with ties broken by  category, and further ties broken by entryID.
  * `l` - clear excerpt list
    `% l`
    Remove all  entries from the  excerpt list.

Output Commands:
  * `g` - print most recent search results
    `% g`
    Log  entries are printed one log  entry per line, sorted by timestamp, with ties broken by category, and further ties broken by  entryID. Each output line should be printed as follows:
    `<entryID>|<timestamp>|<category>|<message><newline>`
  * `p` - print excerpt list
    `% p`
    Excerpt list  entries are printed one entry per line in the order they appear in the excerpt list.

Miscellaneous Commands:
  * `q` - quit
    `% q`
    Terminate the program with non-error status.
  * `#` - no operation
    `% # <string>`
    useful for adding comments to command files
  * `h` - help
    `% h`

## Conclusion
This project helped me gain experience writing code that makes use of multiple interacting data structures. The design portion of this project was significant; spending plenty of time thinking about what data structures to use and how they will interact.

I've gained valuable experience selecting appropriate data structures for a given problem, as well as how to use various abstract data types.
