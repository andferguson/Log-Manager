//logManager.cpp

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <limits>

using namespace std;

///////////////////////////////////////////////////////////
//struct Log_Entrie
struct Log_Entrie {
	string timestamp;
	string category;
	string message;
	int entryID, final_pos;
};

///////////////////////////////////////////////////////////
//struct LOGcomparator
struct LOGcomparator {
	bool operator()(const Log_Entrie* a, const Log_Entrie* b) const {
		if(a->timestamp < b->timestamp) //if a.timestamp is smaller
			return 1;

		else if(a->timestamp > b->timestamp) //if a.timestamp is larger
			return 0;

		else { //if a.timestamp and b.timestamp are equal

			if(a->category < b->category) //if a.category is smaller
				return 1;

			else if(a->category > b->category) //if a.category is larger
				return 0;

			else { //if a.compare and b.compare are equal

				if(a->entryID < b->entryID) //if a.entryID is smaller
					return 1;

				else //a.entryID is larger
					return 0;
			}
		}
	}
};

///////////////////////////////////////////////////////////
//struct TIMEcomparator
struct TIMEcomparator {
	bool operator()(const Log_Entrie* a, const Log_Entrie* b) const {
		if(a->timestamp < b->timestamp) //if a.timestamp is smaller
			return 1;

		else if(a->timestamp > b->timestamp) //if a.timestamp is larger
			return 0;

		else //if a.timestamp and b.timestamp are equal
			return 0;
	}
};

///////////////////////////////////////////////////////////
////////////////////////Begin Main/////////////////////////
///////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	//helps output
	ios_base::sync_with_stdio(false);

	ostringstream os;
	string LOGFILE = {};

	if(argc != 2) {
		cerr << "Error: Improper Arguments " << endl << '\t' << "Use --help or -h" << endl;
		exit(1);
	}

	if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		os << "Log Manager by Andrew Ferguson" << '\n' << '\n'
			<< "This program ..." << '\n'
			<< '\n' << "Flags:" << '\n'
			<< '\t' << "LOGFILE" << '\t' << '\t' << "-specifies the file to read logs from" << '\n'
			<< '\t' << "--help, -h" << '\t' << "-prints this helpful message" << '\n'
			<< '\n' << "Commands:" << '\n'
			<< '\t' << "t ­= timestamp search" << '\n'
			<< '\t' << "Syntax: % t <timestamp1>|<timestamp2>" << '\n' << '\n'
			<< '\t' << "c ­= category search" << '\n'
			<< '\t' << "Syntax: % c <string>" << '\n' << '\n'
			<< '\t' << "k = keyword search" << '\n'
			<< '\t' << "Syntax: % k <string>" << '\n' << '\n'
			<< '\t' << "a = append log entry​(by entryID)" << '\n'
			<< '\t' << "Syntax: % a <integer>" << '\n' << '\n'
			<< '\t' << "r = append search results" << '\n'
			<< '\t' << "Syntax: % r" << '\n' << '\n'
			<< '\t' << "d = delete log entry​(by excerpt list number)" << '\n'
			<< '\t' << "Syntax: % d <integer>" << '\n' << '\n'
			<< '\t' << "b = move to beginning​(by excerpt list number)" << '\n'
			<< '\t' << "Syntax: % b <integer>" << '\n' << '\n'
			<< '\t' << "e = move to end​(by excerpt list number)" << '\n'
			<< '\t' << "Syntax: % e <integer>" << '\n' << '\n'
			<< '\t' << "s = sort excerpt list(by timestamp)" << '\n'
			<< '\t' << "Syntax: % s" << '\n' << '\n'
			<< '\t' << "l = clear excerpt list" << '\n'
			<< '\t' << "Syntax: % l" << '\n' << '\n'
			<< '\t' << "g = print most recent search results" << '\n'
			<< '\t' << "Syntax: % g" << '\n' << '\n'
			<< '\t' << "p = print excerpt list" << '\n'
			<< '\t' << "Syntax: % p" << '\n' << '\n'
			<< '\t' << "q = quit" << '\n'
			<< '\t' << "Syntax: % q" << '\n' << '\n'
			<< '\t' << "# = no operation(useful for adding comments to command files)" << '\n'
			<< '\t' << "Syntax: % # Any text on a line that begins with # is ignored" << '\n' << '\n';
		cout << os.str();
		exit(0);
	}

	else {
		os << "ERROR: use --help or -h" << '\n';
		cout << os.str();
		exit(0);
	}

	LOGFILE = argv[1];

	if(LOGFILE.empty()) {
		cerr << "Error: LOGFILE not read" << endl << '\t' << "argv[1]: " << argv[1] << endl;
		exit(1);
	}

///////////////////////////////////////////////////////////
///////////////////////Take Inputs/////////////////////////
///////////////////////////////////////////////////////////

	LOGcomparator comp;
	TIMEcomparator t_comp;

	int entry_order = 0;
	long pos;
	string line;
	Log_Entrie* entrie_ptr;
	vector<Log_Entrie*> master_log_file;

	ifstream infile(LOGFILE);
	getline(infile, line);

	if(infile.is_open()) {
		if(line.empty()) {
			cerr << "Error: unable to read from file" << endl << '\t' << "LOGFILE: " << LOGFILE << endl;
			exit(1);
		}

		while(!line.empty()) {
			pos = line.find_last_of("|");

			entrie_ptr = new Log_Entrie;

			entrie_ptr->timestamp = line.substr(0, 14);
			entrie_ptr->category = line.substr(15, (pos - 15));
			entrie_ptr->message = line.substr(pos + 1);
			entrie_ptr->entryID = entry_order;

			master_log_file.push_back(entrie_ptr);
			entry_order++;
			getline(infile, line);
		}
		infile.close();
		os << int (master_log_file.size()) << " entries read" << '\n';

		sort(master_log_file.begin(), master_log_file.end(), comp);

		for(int i = 0; i < int (master_log_file.size()); ++i) {
			master_log_file[i]->final_pos = i;
		}
	}

	else {
		cerr << "Error: unable to open file" << endl;
		exit(1);
	}

///////////////////////////////////////////////////////////
///////////////////Main Program Loop///////////////////////
///////////////////////////////////////////////////////////

	deque<int> excerpt_list;
	vector<int> intersect;
	vector<int> result;

	unordered_map<string, vector<int> > categories;
	unordered_map<string, vector<int> > words;

	vector<Log_Entrie*>::iterator search_it1;
	vector<Log_Entrie*>::iterator search_it2;

	Log_Entrie* temp;
	temp = new Log_Entrie;

	string arg, string_arg1, string_arg2, word;
	int int_arg = 0;
	char search = 'n';
	bool first;

	for(vector<Log_Entrie*>::iterator it = master_log_file.begin(); it != master_log_file.end(); ++it) {
		//initialize and sort the master data by category
		arg = (*it)->category;
		transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
		categories[arg].push_back(int_arg);

		//initialize the master data with keywords contained
		arg = (*it)->category;
		arg.push_back(' ');
		arg.append((*it)->message);
		transform(arg.begin(), arg.end(), arg.begin(), ::tolower);

		for(string::iterator that = arg.begin(); that != arg.end(); ++that) {

			// .10
			while(isalnum(*that) != 0 && that != arg.end()) {
				word.push_back(*that);
				++that;
			}

			// .10
			if(!word.empty()) {
				words[word].push_back(int_arg);
				word.clear();
			}

			if(that == arg.end()) {
				break;
			}
		}

		int_arg++;
	}

	os << "% ";
	cin >> arg;

	while(arg != "q") {

//		# = no operation(useful for adding comments to command files)
//		Syntax: % # Any text on a line that begins with # is ignored
		if(arg == "#") {
			getline(cin, string_arg1);
		}

//
//		p = print excerpt list
//		Syntax: % p
		else if(arg == "p") {
			int_arg = 0;
			for(deque<int>::iterator it = excerpt_list.begin(); it != excerpt_list.end(); ++it) {
				os << int_arg << "|"
					<< master_log_file[*it]->entryID
					<< "|" << master_log_file[*it]->timestamp
					<< "|" << master_log_file[*it]->category
					<< "|" << master_log_file[*it]->message << '\n';
				int_arg++;
			}
		}

//		g = print most recent search results
//		Syntax: % g
		else if(arg == "g") {
			if(search == 'n') {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				if(search == 'c') {
					if(categories.count(word)) {
						for(vector<int>::iterator it = categories[word].begin(); it != categories[word].end(); ++it) {
							os << master_log_file[*it]->entryID << "|"
								<< master_log_file[*it]->timestamp << "|"
								<< master_log_file[*it]->category << "|"
								<< master_log_file[*it]->message << '\n';
						}
					}
				}

				else if(search == 't' || search == 'm') {
					for(vector<Log_Entrie*>::iterator it = search_it1; it != search_it2; ++it) {
						os << (*it)->entryID << "|"
							<< (*it)->timestamp << "|"
							<< (*it)->category << "|"
							<< (*it)->message << '\n';
					}
				}

				else { //(search == 'k')
					for(vector<int>::iterator it = intersect.begin(); it != intersect.end(); it++) {
						os << master_log_file[*it]->entryID << "|"
							<< master_log_file[*it]->timestamp << "|"
							<< master_log_file[*it]->category << "|"
							<< master_log_file[*it]->message << '\n';
					}
				}
			}
		}

//		l = clear excerpt list ​
//		Syntax: % l
		else if(arg == "l") {
			excerpt_list.clear();
			os << "excerpt list cleared" << '\n';
		}

//		s = sort excerpt list(by timestamp)
//		Syntax: % s
		else if(arg == "s") {
			sort(excerpt_list.begin(), excerpt_list.end());
			os << "excerpt list sorted" << '\n';
		}

//		b = move to beginning​(by excerpt list number)
//		Syntax: % b <integer>
		else if(arg == "b") {
			cin >> int_arg;
			if(int_arg >= int (excerpt_list.size())) {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				excerpt_list.push_front(excerpt_list[int_arg]);
				excerpt_list.erase(excerpt_list.begin()+ int_arg + 1);
				os << "Moved excerpt list entry " << int_arg << '\n';
			}
		}

//		e = move to end​(by excerpt list number)
//		Syntax: % e <integer>
		else if(arg == "e") {
			cin >> int_arg;
			if(int_arg >= int (excerpt_list.size())) {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				excerpt_list.push_back(excerpt_list[int_arg]);
				excerpt_list.erase(excerpt_list.begin() + int_arg);
				os << "Moved excerpt list entry " << int_arg << '\n';
			}
		}

//		t ­= timestamp search
//		Syntax: % t <timestamp1>|<timestamp2>
		else if(arg == "t") {
			cin >> string_arg1;
			if(int (string_arg1.size()) != 29) {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				string_arg2 = string_arg1.substr(15,14);
				string_arg1 = string_arg1.substr(0,14);

				temp->timestamp = string_arg1;
				search_it1 = lower_bound(master_log_file.begin(), master_log_file.end(), temp, t_comp);
				temp->timestamp = string_arg2;
				search_it2 = upper_bound(master_log_file.begin(), master_log_file.end(), temp, t_comp);

				//need replacement for distance O(log(n)) => O(1)
				os << "Timestamps search: " << distance(search_it1, search_it2) << " entries found" << '\n';
				search = 't';
			}
		}

//		m ­= matching search
//		Syntax: % m <timestamp1>
		else if(arg == "m") {
			cin >> string_arg1;
			if(int (string_arg1.size()) != 14) {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				temp->timestamp = string_arg1;
				search_it1 = lower_bound(master_log_file.begin(), master_log_file.end(), temp, t_comp);
				search_it2 = upper_bound(master_log_file.begin(), master_log_file.end(), temp, t_comp);

				//need replacement for distance O(log(n)) => O(1)
				os << "Timestamp search: " << distance(search_it1, search_it2) << " entries found" << '\n';
				search = 'm';
			}
		}

//		c ­= category search
//		Syntax: % c <string>
		else if(arg == "c") {
			getline(cin, string_arg1);
			string_arg1.erase(0,1);
			transform(string_arg1.begin(), string_arg1.end(), string_arg1.begin(), ::tolower);

			word = string_arg1;
			if(categories.count(word)) {
				os << "Category search: " << categories[word].size() << " entries found" << '\n';
			}

			else {
				os << "Category search: 0 entries found" << '\n';
			}
			search = 'c';
		}

//		k = keyword search
//		Syntax: % k <string>
		else if(arg == "k") {
			getline(cin, string_arg1);
			transform(string_arg1.begin(), string_arg1.end(), string_arg1.begin(), ::tolower);

			first = 1;
			word.clear();

			for(string::iterator it = string_arg1.begin(); it != string_arg1.end(); ++it) {
				while(isalnum(*it) != 0 && it != string_arg1.end()) {
					word.push_back(*it);
					++it;
				}

				if(!word.empty()) {
					if(first) {
						intersect.clear();
						intersect = words[word];
						auto last = unique(intersect.begin(), intersect.end());
						intersect.erase(last, intersect.end());

						first = 0;
					}

					else {
						result.clear();
						set_intersection(intersect.begin(), intersect.end(), words[word].begin(), words[word].end(), back_inserter(result));
						intersect = result;
					}
					word.clear();
				}

				if(it == string_arg1.end() || (!first && intersect.empty())) {
					break;
				}
			}

			os << "Keyword search: " << intersect.size() << " entries found" << '\n';
			search = 'k';
		}

//		a = append log entry​(by entryID)
//		Syntax: % a <integer>
		else if(arg == "a") {
			cin >> int_arg;
			if(int_arg >= int (master_log_file.size()) || int_arg < 0) {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				for(int i = 0; i < int (master_log_file.size()); ++i) {
					if((master_log_file[i])->entryID == int_arg) {
						excerpt_list.push_back(i);
						break;
					}
				}

				os << "log entry " << int_arg << " appended" << '\n';
			}
		}

//		r = append search results
//		Syntax: % r
		else if(arg == "r") {
			if(search == 'n') {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				int_arg = 0;
				if(search == 'c') {
					if(categories.count(word)) {
						for(vector<int>::iterator it = categories[word].begin(); it != categories[word].end(); ++it) {
							excerpt_list.push_back(*it);
							int_arg++;
						}
					}
				}

				else if(search == 't' || search == 'm') {
					for(vector<Log_Entrie*>::iterator it = search_it1; it != search_it2; ++it) {
						excerpt_list.push_back((*it)->final_pos);
						int_arg++;
					}
				}

				else { //(search == 'k')
					for(vector<int>::iterator it = intersect.begin(); it != intersect.end(); ++it) {
						excerpt_list.push_back(*it);
						int_arg++;
					}
				}

				os << int_arg << " log entries appended" << '\n';
			}
		}

//		d = delete log entry​(by excerpt list number)
//		Syntax: % d <integer>
		else if(arg == "d") {
			cin >> int_arg;
			if(int_arg >= int (excerpt_list.size())) {
				cerr << "Error: Invalid command" << endl;
			}

			else {
				excerpt_list.erase(excerpt_list.begin() + int_arg);
				os << "Deleted excerpt list entry " << int_arg << '\n';
			}
		}

		else {
			cerr << "Error: Invalid command" << endl;
		}

		//promt for next command
		os << "% ";
		cin >> arg;
	}

	//delete the data
	for(vector<Log_Entrie*>::iterator it = master_log_file.begin(); it != master_log_file.end(); ++it) {
		delete *it;
	}

	delete temp;
	cout << os.str();
	return 0;
}

///////////////////////////////////////////////////////////
///////////////////////End of File/////////////////////////
///////////////////////////////////////////////////////////
