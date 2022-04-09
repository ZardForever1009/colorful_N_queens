#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cmath>
#include <windows.h>

using namespace std;

// change color
void change_color(WORD c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return;
}

// change output char color
void color_char(string stats, char c, bool new_line){
	if(stats=="user_queen")change_color(FOREGROUND_RED|FOREGROUND_GREEN);
	else if(stats=="queen")change_color(FOREGROUND_RED|FOREGROUND_INTENSITY);
	else if(stats=="normal")change_color(FOREGROUND_BLUE|FOREGROUND_GREEN);
	else{
		change_color(FOREGROUND_RED);
		cout<<"No matched stats instruction";
	}
	cout<<c;
	change_color(7);
	if(new_line)cout<<endl;
	return;
}


// change output string color
void color_str(string stats, string line, bool new_line){
	if(stats=="info"||stats=="input")change_color(FOREGROUND_RED|FOREGROUND_GREEN);
	else if(stats=="number")change_color(FOREGROUND_GREEN);
	else if(stats=="normal")change_color(7);
    else{                     
        change_color(FOREGROUND_RED);
        cout<<"No matched stats instruction";
    }
	cout<<line;
	change_color(7);
	if(new_line)cout<<endl;
	return;
} 

// yes or not
bool yes_or_not(const string ques){
	bool okay=false;
	string ans;
	while(!okay){
		color_str("input", ques, false);
		getline(cin, ans);
		if(ans=="y"||ans=="Y")return true;
		else if(ans=="n"||ans=="N")return false;
		else color_str("normal", "failed: Only 'y' or 'n'", true);
	}
}

// get user input
string get_input(const string line, bool int_only, int min, int max){
	string input;
	bool okay=false;
	while(!okay){
		ENTER:
		color_str("input", line, false);
		getline(cin, input);
		if(input.size()==0){ //empty input
			color_str("normal", "failed: empty input\n", true);
			goto ENTER;
		}
		if(int_only){
			for(int i=0;i<input.size();i++){
				if(!isdigit(input[i])){
					color_str("normal", "failed: integer only\n", true);
					goto ENTER;
				}
				else if(i==input.size()-1)okay=true;
			}
			if(stoi(input)>max||stoi(input)<min){
				color_str("normal", "failed: invalid input\n", true);
				okay=false;
			}
		}
		else okay=true;
	}
	return input;
}

// program info
string setup(){
	color_str("info", "====================Eight Queens=====================",true);
	color_str("normal", "> No two queens share the same row/column/diagonal", true);
	color_str("normal", "> User choose the column of 1st row to place queen", true);
	color_str("normal", "> Queen is denoted by 'Q'", true);
	color_str("normal", "> Civilian is denoted by '-'", true);
	color_str("info", "\n> creator: zardforever", true);
    color_str("info", "=====================================================", true);
	color_str("info", "\n========Choose Queen's Column Position========", true);
	string result=get_input("Queen Column[1~8]: ", true, 1, 8);
	return result;
}

// check if a grid is valid for placing a queen
bool grid_good(vector<vector<char>> table, int row, int col){
	cout<<"GRID: "<<row<<"/"<<col<<endl;
	// horizontal
	for(int i=0;i<table.size();i++){
		if(table[row][i]=='Q')return false;
	}
	// vertical
	for(int i=0;i<table.size();i++){
		if(table[i][col]=='Q')return false;
	}
	// diagonal
	for(int i=0;i<table.size();i++){
		for(int j=0;j<table.size();j++){
			if(table[i][j]=='Q'){
				cout<<"AAA"<<endl;
				cout<<i<<"/"<<j<<" "<<row<<"/"<<col<<endl;
				if(abs(row-i)==abs(col-j)){
					return false;
				}
				else;
			}
			else;
		}
	}
	return true;
}

// prnt list func
void print_result(vector<vector<char>> table){
	color_str("info", "=======Eight Queens Result========",true);
	cout<<"   ";
	for(int i=0;i<table.size();i++){
		color_str("number", to_string(i+1)+" ", false);
	}
	color_str("number", "\n====", false);
	for(int i=0;i<table.size();i++){
		color_str("number", "==", false);
	}
	cout<<endl;
	for(int i=0;i<table.size();i++){
		color_str("number", to_string(i+1)+"| ", false);
		for(int j=0;j<table.size();j++){
			if(table[i][j]=='Q'&&i==0)color_char("user_queen", table[i][j], false);
			else if(table[i][j]=='Q')color_char("queen", table[i][j],false);
			else color_char("normal", table[i][j], false);
			cout<<" ";
		}
		color_str("number", "|\n", false);
	}
	color_str("number", "====", false);
	for(int i=0;i<table.size();i++){
		color_str("number", "==", false);
	}
	color_str("info", "\n==================================",true);
}

// stack method
void stack_m(vector<vector<char>>& table, int queen_col){
	stack<int> st;
	st.push(queen_col);
	int curr_row=1, curr_col=0;
	while(curr_row<table.size()){
		if(curr_col>=table.size()){
			curr_row=curr_row-1;
			table[curr_row][st.top()]='-';
			curr_col=st.top()+1;
			st.pop();
		}
		else if(grid_good(table, curr_row, curr_col)){
			print_result(table);
			table[curr_row][curr_col]='Q';
			st.push(curr_col);
			curr_row=curr_row+1;
			curr_col=0;
		}
		else{ 
			curr_col=curr_col+1;
		}
	}
	print_result(table);
	return;
}



int main(){	
	bool again=true;
	while(again){
		int col=stoi(setup())-1;
		system("cls");
		vector<vector<char>> table(8, vector<char>(8, '-'));
		table[0][col]='Q';
		stack_m(table, col);
		again=yes_or_not("Do you want to continue?? [y/n] ");
		system("cls");
	}
	return 0;
}