Your executable program will be called logman. The program will begin by reading an input file containing log entries, and then will enter an interactive mode where the user can perform  timestamp, category, and  keyword searches for the purpose of constructing an "excerpt list" of the log file.  logman also allows the user to manage and display this "excerpt list" to identify the important/relevant entries of their log file.

Input: Master Log File
On startup,  logman  reads  a series of log entries from the  master log file, a file specified via the command line. The file is a plain text file which describes a single log entry on every line. Each log entry consists of three fields separated by vertical bar ( '|' ) characters. The first field contains the timestamp o f the log entry, the second contains the c  ategory of the log entry, and the third contains the message of the log entry. The following is a description of the formats of each field:

Log  timestamps will be given in the format m  m:dd:hh:mm:s s , where the various components (month, day, hour, minute, second) between colons are given as a pair of digits. Note that there will always be two digits so that numbers such as  7  are represented as " 07 ". You do not need to check that the digits in each field ‘make sense’. If it says ‘99’ for minutes, that is OK, and is still a valid timestamp. Further,  00:00:00:01:00   is later than 0  0:00:00:00:61   regardless of true values in total seconds. Similarly,  00:00:01:00:00   is later than 0  0:00:00:61:00  , etc. This is to make input parsing easier.

Log  categories will be given as strings and correspond to some general, but meaningful, description of which part of the  logged program outputted the message. Log c  ategories must always contain at least one character, will be constructed of ASCII characters between 32 ('  ' ) and 126 ( '~' ) inclusive, will not contain the bar character ('  |' ), and will not have any leading or trailing whitespace.

Log  messages will be given as strings containing characters between 32 ('  ' ) and 126 ('  ~' ) inclusive, but not the bar character ('  |' ). Log m  essages will contain at least one alphanumeric character before the terminating newline, and will not have any leading or trailing whitespace. There will be exactly two bar characters ('  |' ) in every log entry

An example of two lines from the  master log file:
10:09:03:45:50|TCP|Packet 0x4235124 sent
09:15:12:00:00|Clock|Noon 09/15

what you run:
logman myLogFile.txt < commandInput.txt > yourStandardOutput.txt
