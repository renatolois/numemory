#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h>
#include <ncurses.h>
#include <csignal>
#include <cstring>
#include <cstdio>
#include "chartoi.hpp"

#define DELAY 1

using namespace std;

// Show --help for user
void show_help(const char* command);

// Handler for Ctrl C
void keybint_handler(int sig);

// Generates a 9-digit number with qnum digits
int generate9(int qnum);

// main function
int main(int argc, char** argv) {
	double SEC = 3;
	int QNUM = 7;

	// processing args
	if(argc > 1) {
		for(int i=1; i<argc; i++) {
			if( strcmp(argv[i], "--help") == 0 ) {
				show_help(argv[0]);
				exit(0);
			}
			else if( strcmp(argv[i], "-q") == 0 ) {
				QNUM = chartoi(argv[++i]);
				if(QNUM < 1 || QNUM > 8) {
				cout << argv[0] << " invalid argument for -q \"" << argv[i] << "\"\n"
						 << "\ntry 'numemory --help' for more information\n";
					return 0;
				}
			}
			else if( strcmp(argv[i], "-t") == 0 ) {
				SEC = chartoi(argv[++i]);
				if(SEC < 0) {
					cout << argv[0] << " invalid argument for -t \"" << argv[i] << "\"\n"
							 << "\ntry 'numemory --help' for more information\n";
					return 0;
				}
			} else {
				cout << "numemory: invalid option: " << argv[1] << "\ntry 'numemory --help' for more information\n";
				exit(1);
			}
		}
	}

	// format for input
	char format[5];
	sprintf(format, "%%%ds", QNUM);

	// for randomize numbers
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<long long> dist(0, generate9(QNUM));

	// screen dimensions
	int row, col;

	// enabling Ctrl C handler
	signal(SIGINT, keybint_handler);
	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, row, col);

	// player points
	int pts = 0;
	// player input
	char res[9];
	// original number
	char num[9];
	// level for increase speed
	int level = 0;

	// dashboard
	mvprintw(row/2 - 1, (col - 8) / 2, "NUMEMORY");
	mvprintw(row/2 + 1, (col - 22) / 2, "Press any key to enter");
	getch();
	clear();

	// program begin
	while(1) {
		// int to char*
		ostringstream oss;
	  oss << setw(QNUM) << setfill('0') << dist(mt);
		strncpy(num, oss.str().c_str(), QNUM);
		num[QNUM] = '\0';

		
		mvprintw(row/2 + 4, (col - 11) / 2, "Starting...");
		refresh();
		sleep(DELAY);
		move(row/2 + 4, 0);
		clrtoeol();

		mvprintw(row - 2, 2, "Ctrl C to exit");
		mvprintw(row - 2, col - 20, "points: %d", pts);
		mvprintw( 3, 3, "difficulty: %d", (int) (100 / SEC) );

		move(row/2, (col - QNUM * 2 - 1)/2);
		for(int i=0; i<QNUM; i++) {
			addch(' ');
			addch(num[i]);
		}

		refresh();
		sleep(SEC);
		move(row/2, 0);
		clrtoeol();
		move(row/2, 0);
		clrtoeol();
		echo();
		curs_set(1);

		flushinp();
		mvscanw(row/2 + 5, (col-QNUM)/2, format, res);
		res[QNUM] = 0;
		move(row/2 + 5, 0);
		clrtoeol();

		noecho();
		curs_set(0);

		if( strcmp(res, num) == 0 ) {
			mvprintw(row - 2, col - 3, "+1");
			pts++;
			if(level % 3 == 0) SEC *= 0.95;
			level++;
		}
		else {
			mvprintw(row - 2, col - 3, "+0");
		}
	}

end:

	getch();
	endwin();
	cout << res << endl << num << endl << pts << endl;
	return 0;
}

void show_help(const char* command) {
	cout << "Usage: " << command << " [options]\n\n"
			 << "Options:\n"
			 << "\t-t <time>      Time in seconds that the numbers stay on the screen (default: 3)\n"
			 << "\t-q <quantity>  Number of digits of the number, -q must be > 0 and < 8 (default: 7)\n"
			 << "\t--help         Displays this help\n\n"
			 << "Example:\n"
			 << "\t" << command << " -t 5 -q 4\n";
}

void keybint_handler(int sig) {
	endwin();
	exit(1);
}

int generate9 (int qnum) {
	int num = 0;
	for(int i=0; i<qnum; i++) {
		num = num * 10 + 9;
	}
	return num;
}
