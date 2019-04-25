//============================================================================
// Name        : datastructure2-2.cpp
// Author      : Hyunju Kim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>//문제2번
#include <fstream>
#include <cstdlib>
using namespace std;

bool isOpen(char ch);//입력받은 ch가 open인지 확인하는 함수
bool isClosed(char ch);//입력받은 ch가 close인지 확인하는 함수
bool matches(char ch, char openSymbol);//짝이 맞는지 확인하는 함수
void errorcheck(bool, char ch, char openSymbol);//에러 체크하는 함수


typedef char ItemType;               //typedef 사용
const int MAX_STACK_SIZE=100;       // 스택의 최대 크기 설정


class Stack
{
	int top;                       // 스택에서 가장 위에 있는 요소의 배열위치
    ItemType data[MAX_STACK_SIZE]; // 요소를 저장하는 배열

public:
    Stack();		               // 스택 생성자
    ~Stack();                      // 스택 소멸자
    bool isEmpty();				   // 비어있는지 확인하는 함수
    bool isFull();				   // 다 차있는지 확인하는 함수
    void push(char ch);        // 스택에 요소 삽입
    ItemType pop(); 	           // 가장 최근에 스택에 삽입된 요소를 삭제하고 반환
    ItemType peek(); 	           // 가장 최근에 스택에 삽입된 요소를 반환
};


inline void error(char const *message)//에러 메세지 출력
{
	cout<< message <<endl;
	exit(1);
}


Stack::Stack(){ top=-1;}//스택 생성자
Stack::~Stack(){}//스택 소멸자

bool Stack:: isEmpty()//비었는지 확인하는 함수
{

	return top == -1;//비어있으면 -1반환
}

bool Stack::isFull()//다 차있는지 확인
{
	return top == MAX_STACK_SIZE-1;//다 차있기 때문에 전체 배열크기-1
}

void Stack::push(char ch)//ch을 stack에 입력
{
	if(isFull())//다 차있으면
	{
		error("스택 Full");
	}
	//data[top++]=e;랑 같은 의미
	else//안차있으므로
	{
		top++;//top을 증가시킴
		data[top]=ch;//ch값을 data[top]에 넣기
	}
}


ItemType Stack::pop()
{
	if(isEmpty())
	{
		error("스택 Empty");
	}
	return data[top--];//하나 지웠으므로 top 1감소
}

ItemType Stack::peek()
{
	if(isEmpty())
	{
		error("스택 Empty");
	}
	return data[top];//현재 top이 가진 값을 반환
}



int main()
{
	char ch;//넣을 괄호
	Stack stack;//클래스 스택선언
	bool balanced = true;//스택이 비어있으면 balanced
	char openSymbol;//오픈괄호 의미

	//파일 filename으로 부터 입력, 구름이에게는 cin.get으로

	while(cin.get(ch) && balanced)//cin.get(ch)를 통해 입력받기
	{
		if (isOpen(ch))//여는괄호일 때
		{
			stack.push(ch);//스택에 저장
		}

		else if(isClosed(ch))//닫는 괄호일 때
		{
			if(stack.isEmpty())//비어있는지 확인, 만약 비어있다면, 왼쪽 괄호가 없는 것이므로
			{
				openSymbol=0;
				balanced=false;//짝이 맞지 않다

				if(!balanced)//짝이 맞지 않다면
				{
					errorcheck(balanced, ch, openSymbol);//에러체크
				}

				break;
			}

			else//비어있지 않다면
			{
				openSymbol=stack.pop();//스택의 pop할 char을 openSymbol에 넣기(왼쪽괄호)

				balanced=matches(ch, openSymbol);//ch와 openSymbol(왼쪽괄호)의 짝이 같은지 확인, 맞으면 1, 다르면 -1

				if(!balanced)//balanced가 맞지 않다면
				{
					errorcheck(balanced, ch, openSymbol);//에러체크
				}
			}
		}
	}

	if(stack.isEmpty() && balanced)//스택이 다 비워져있으면 짝이 다 맞다는 말
	{
		cout<<"1"<<endl;
	}

	else if(!balanced){ }//위에서 써줬으므로 생략
	else if(!stack.isEmpty())//비어있지 않다면
	{
		openSymbol=stack.pop();//openSymbol에 pop해서 넣기
		errorcheck(balanced, ch, openSymbol);
	}

	else
	{
		errorcheck(balanced, ch, openSymbol);
	}

	//sIN.close();
	return 0;
}



bool isOpen(char ch)//여는 괄호가 들어왔을 때
{
	if((ch =='(') || (ch =='{') || (ch == '['))
	{
		return true;//맞으면 참
	}

	else
	{
		return false;//아니면 거짓
	}
}

bool isClosed(char ch)//닫는 괄호가 들어왔을 때
{
	if((ch == ')') || (ch == '}') ||(ch == ']'))
	{
		return true;//이것 중 하나면 참임
	}

	else
	{
		return false;//아니면 거짓
	}
}

bool matches(char ch, char openSymbol)//짝이 맞는지 확인
{
	if(((openSymbol == '(') && ch == ')') || ((openSymbol == '{') && ch == '}') || ((openSymbol == '[') && ch == ']'))
	{
		return true;//맞으면 참
	}

	else
	{
		return false;//아니면 거짓
	}
}

void errorcheck(bool balanced, char ch, char openSymbol)
	//ch와 openSymbol의 상태로 error번호 찾기
{
	if((ch == ')') && (openSymbol != '('))//)에 대응하는 (가 없을 경우
	{
		cout<<"error 1";
	}

	else if((ch == '}') && (openSymbol != '{'))//}에 대응하는 {가 없을 경우
	{
		cout<<"error 2";
	}

	else if((ch == ']') && (openSymbol != '['))//]에 대응하는 [가 없을 경우
	{
		cout<<"error 3";
	}

	else if((openSymbol == '(') && (ch != ')'))//(에 대응하는 )가 없을 경우
	{
		cout<<"error 4";
	}

	else if((openSymbol == '{') && (ch != '}'))//{에 대응하는 }가 없을 경우
	{
		cout<<"error 5";
	}

	else if((openSymbol == '[') && (ch != ']'))//[에 대응하는 ]가 없을 경우
	{
		cout<<"error 6";
	}
}
