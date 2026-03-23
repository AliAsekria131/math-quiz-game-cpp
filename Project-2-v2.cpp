#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
enum enQuestionLevel{Easy = 1, Mid, Hard, Mix};
enum enOperationType{Add=1, Sub, Mul,Div,MixOp};
struct stQuestion{
	int Number1;
	int Number2;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	int CurrentAnswer;
	int PlayerAnswer;
	bool AnswerResult;
};
struct stQuezz{
	stQuestion Questions[100];
	int NumberOfQuestion;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int NumberRightAnswars;
	int NumberWrongAnswers;
};
int RandomNumber(int From, int To){
	return rand() % (To - From + 1) + From;
}
// Input Setting
int ReadNumberOfQuestion(){
	int N;
	do{
		cout << "How Many Questions do you went to Answers? ";
		cin >> N;
	}while(N < 1 && N > 20);
	return N;
}
enQuestionLevel ReadQuestionLevel(){
	int N;
	do{
		cout << "Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? "<< endl;
		cin >> N;
	}while(N > 3 && N < 1);
	return enQuestionLevel(N);
}
enOperationType ReadOperationType(){
	int N;
	do{
		cout << "Enter Operations Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? " << endl;
		cin >> N;
	}while(N < 1 && N > 5);
	return enOperationType(N);
}

int GenerateNumber(enQuestionLevel Level){
	if(Level == Mix){
		return RandomNumber(1,100);
	}
	switch(Level){
	case Easy:
		return RandomNumber(0,10);
	case Mid:
		return RandomNumber(10,50);
	case Hard:
		return RandomNumber(50,100);
	default:
		return (0,10);
	}
}

enOperationType GenerateOperationType(enOperationType Type){
	if(Type == MixOp){
		return enOperationType(RandomNumber(1,4));
	}
	else 
		return Type;
}

int CalCurrentAnswer(int N1,int N2, enOperationType OperationType){
	switch(OperationType){
	case Add:
		return N1 + N2;
		break;
	case Sub:
		return N1 - N2;
		break;
	case Mul:
		return N1 * N2;
		break;
	case Div:
		return N1 / N2;
		break;
	default:
		return N1 + N2;
	}

}

stQuestion GenerateQuestion(stQuezz Quezz){
	stQuestion Question;
	Question.Number1 = GenerateNumber(Quezz.QuestionLevel);
	Question.Number2 = GenerateNumber(Quezz.QuestionLevel);
	Question.OperationType = GenerateOperationType(Quezz.OperationType);

	Question.CurrentAnswer = CalCurrentAnswer(Question.Number1, Question.Number2,Question.OperationType);
	return Question;
}
void GenerateQuezzQuestions(stQuezz &Quezz){
	for(int i=0; i< Quezz.NumberOfQuestion ;i++){
		Quezz.Questions[i] = GenerateQuestion(Quezz);
	}
}
int ReadAnswerPlayer(){
	int Answer;
	cin >> Answer;
	return Answer;
}
void SetAnswerResultState(stQuestion &Question){
	if(Question.CurrentAnswer == Question.PlayerAnswer)
		Question.AnswerResult = true;
	else
		Question.AnswerResult = false;
}
string GetTextFromOptype(enOperationType Type){
	string TextType[5] = {"+", "-", "*", "/"};
	return TextType[int(Type) - 1];
}
void AskPlayerForAnswer(stQuezz &Quezz){
	for(int i=0;i<Quezz.NumberOfQuestion;i++){
		cout << Quezz.Questions[i].Number1 << endl;
		cout << Quezz.Questions[i].Number2 <<" " << GetTextFromOptype( Quezz.Questions[i].OperationType )<< endl;
		cout << "__________" << endl;
		Quezz.Questions[i].PlayerAnswer = ReadAnswerPlayer();
		SetAnswerResultState(Quezz.Questions[i]);
		if(Quezz.Questions[i].AnswerResult){
			Quezz.NumberRightAnswars ++ ;
			cout << "Right Answer :]"<< endl << endl;
		}
		else{
			cout << "Wrong Answer :[" << endl << endl;
			Quezz.NumberWrongAnswers ++;
		}
	}
}
string GetTextFromQuestionLevel(enQuestionLevel Level){
	string TextLevel[4] = {"Easy" , "Mid" , "Hard" ,"Mix"};
	return TextLevel[int(Level)-1];
}

void PrintGameResult(stQuezz Quezz){
	cout << "Number of Questions: " << Quezz.NumberOfQuestion << endl;
	cout << "Questions level: " << GetTextFromQuestionLevel(Quezz.QuestionLevel) << endl;
	cout << "Optype: " << GetTextFromOptype(Quezz.OperationType) << endl;
	cout << "Number of Right Answers: " << Quezz.NumberRightAnswars << endl;
	cout << "Number of wrong Answers: " << Quezz.NumberWrongAnswers << endl;
}

void PlayMathGame(){
	stQuezz Quezz;
	Quezz.NumberRightAnswars = 0;
	Quezz.NumberWrongAnswers = 0;
	Quezz.NumberOfQuestion = ReadNumberOfQuestion();
	Quezz.QuestionLevel = ReadQuestionLevel();
	Quezz.OperationType = ReadOperationType();

	GenerateQuezzQuestions(Quezz);

	AskPlayerForAnswer(Quezz);
	PrintGameResult(Quezz);
}
void ResetGame(){
	system("cls");
}
void StartMathGame(){
	char AskAgain;
	do{
		ResetGame();
		PlayMathGame();
		cout << endl << "Do you went to play again? ";
		cin >> AskAgain;
	}while(AskAgain == 'Y' || AskAgain == 'y');
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned) time(NULL));

	StartMathGame();

	return 0;
}

