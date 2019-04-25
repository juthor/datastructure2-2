//============================================================================
// Name        : datastructure2-2.cpp
// Author      : Hyunju Kim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>//����2��
#include <fstream>
#include <cstdlib>
using namespace std;

bool isOpen(char ch);//�Է¹��� ch�� open���� Ȯ���ϴ� �Լ�
bool isClosed(char ch);//�Է¹��� ch�� close���� Ȯ���ϴ� �Լ�
bool matches(char ch, char openSymbol);//¦�� �´��� Ȯ���ϴ� �Լ�
void errorcheck(bool, char ch, char openSymbol);//���� üũ�ϴ� �Լ�


typedef char ItemType;               //typedef ���
const int MAX_STACK_SIZE=100;       // ������ �ִ� ũ�� ����


class Stack
{
	int top;                       // ���ÿ��� ���� ���� �ִ� ����� �迭��ġ
    ItemType data[MAX_STACK_SIZE]; // ��Ҹ� �����ϴ� �迭

public:
    Stack();		               // ���� ������
    ~Stack();                      // ���� �Ҹ���
    bool isEmpty();				   // ����ִ��� Ȯ���ϴ� �Լ�
    bool isFull();				   // �� ���ִ��� Ȯ���ϴ� �Լ�
    void push(char ch);        // ���ÿ� ��� ����
    ItemType pop(); 	           // ���� �ֱٿ� ���ÿ� ���Ե� ��Ҹ� �����ϰ� ��ȯ
    ItemType peek(); 	           // ���� �ֱٿ� ���ÿ� ���Ե� ��Ҹ� ��ȯ
};


inline void error(char const *message)//���� �޼��� ���
{
	cout<< message <<endl;
	exit(1);
}


Stack::Stack(){ top=-1;}//���� ������
Stack::~Stack(){}//���� �Ҹ���

bool Stack:: isEmpty()//������� Ȯ���ϴ� �Լ�
{

	return top == -1;//��������� -1��ȯ
}

bool Stack::isFull()//�� ���ִ��� Ȯ��
{
	return top == MAX_STACK_SIZE-1;//�� ���ֱ� ������ ��ü �迭ũ��-1
}

void Stack::push(char ch)//ch�� stack�� �Է�
{
	if(isFull())//�� ��������
	{
		error("���� Full");
	}
	//data[top++]=e;�� ���� �ǹ�
	else//���������Ƿ�
	{
		top++;//top�� ������Ŵ
		data[top]=ch;//ch���� data[top]�� �ֱ�
	}
}


ItemType Stack::pop()
{
	if(isEmpty())
	{
		error("���� Empty");
	}
	return data[top--];//�ϳ� �������Ƿ� top 1����
}

ItemType Stack::peek()
{
	if(isEmpty())
	{
		error("���� Empty");
	}
	return data[top];//���� top�� ���� ���� ��ȯ
}



int main()
{
	char ch;//���� ��ȣ
	Stack stack;//Ŭ���� ���ü���
	bool balanced = true;//������ ��������� balanced
	char openSymbol;//���°�ȣ �ǹ�

	//���� filename���� ���� �Է�, �����̿��Դ� cin.get����

	while(cin.get(ch) && balanced)//cin.get(ch)�� ���� �Է¹ޱ�
	{
		if (isOpen(ch))//���°�ȣ�� ��
		{
			stack.push(ch);//���ÿ� ����
		}

		else if(isClosed(ch))//�ݴ� ��ȣ�� ��
		{
			if(stack.isEmpty())//����ִ��� Ȯ��, ���� ����ִٸ�, ���� ��ȣ�� ���� ���̹Ƿ�
			{
				openSymbol=0;
				balanced=false;//¦�� ���� �ʴ�

				if(!balanced)//¦�� ���� �ʴٸ�
				{
					errorcheck(balanced, ch, openSymbol);//����üũ
				}

				break;
			}

			else//������� �ʴٸ�
			{
				openSymbol=stack.pop();//������ pop�� char�� openSymbol�� �ֱ�(���ʰ�ȣ)

				balanced=matches(ch, openSymbol);//ch�� openSymbol(���ʰ�ȣ)�� ¦�� ������ Ȯ��, ������ 1, �ٸ��� -1

				if(!balanced)//balanced�� ���� �ʴٸ�
				{
					errorcheck(balanced, ch, openSymbol);//����üũ
				}
			}
		}
	}

	if(stack.isEmpty() && balanced)//������ �� ����������� ¦�� �� �´ٴ� ��
	{
		cout<<"1"<<endl;
	}

	else if(!balanced){ }//������ �������Ƿ� ����
	else if(!stack.isEmpty())//������� �ʴٸ�
	{
		openSymbol=stack.pop();//openSymbol�� pop�ؼ� �ֱ�
		errorcheck(balanced, ch, openSymbol);
	}

	else
	{
		errorcheck(balanced, ch, openSymbol);
	}

	//sIN.close();
	return 0;
}



bool isOpen(char ch)//���� ��ȣ�� ������ ��
{
	if((ch =='(') || (ch =='{') || (ch == '['))
	{
		return true;//������ ��
	}

	else
	{
		return false;//�ƴϸ� ����
	}
}

bool isClosed(char ch)//�ݴ� ��ȣ�� ������ ��
{
	if((ch == ')') || (ch == '}') ||(ch == ']'))
	{
		return true;//�̰� �� �ϳ��� ����
	}

	else
	{
		return false;//�ƴϸ� ����
	}
}

bool matches(char ch, char openSymbol)//¦�� �´��� Ȯ��
{
	if(((openSymbol == '(') && ch == ')') || ((openSymbol == '{') && ch == '}') || ((openSymbol == '[') && ch == ']'))
	{
		return true;//������ ��
	}

	else
	{
		return false;//�ƴϸ� ����
	}
}

void errorcheck(bool balanced, char ch, char openSymbol)
	//ch�� openSymbol�� ���·� error��ȣ ã��
{
	if((ch == ')') && (openSymbol != '('))//)�� �����ϴ� (�� ���� ���
	{
		cout<<"error 1";
	}

	else if((ch == '}') && (openSymbol != '{'))//}�� �����ϴ� {�� ���� ���
	{
		cout<<"error 2";
	}

	else if((ch == ']') && (openSymbol != '['))//]�� �����ϴ� [�� ���� ���
	{
		cout<<"error 3";
	}

	else if((openSymbol == '(') && (ch != ')'))//(�� �����ϴ� )�� ���� ���
	{
		cout<<"error 4";
	}

	else if((openSymbol == '{') && (ch != '}'))//{�� �����ϴ� }�� ���� ���
	{
		cout<<"error 5";
	}

	else if((openSymbol == '[') && (ch != ']'))//[�� �����ϴ� ]�� ���� ���
	{
		cout<<"error 6";
	}
}
