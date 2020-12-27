//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"",	 "netup",							30, 		0},
	{"bat", "batt & battwarn", 	 					25, 		0},
	{"vol:", "vol", 							2,		0},
	{"", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",		10,		0},
	{"", "date '+%a-%b-%d-%-I:%M%p'",					30,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "| ";
static unsigned int delimLen = 5;
