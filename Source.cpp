#include<iostream>
#include<string>
#include<stack>
#include<cmath>
using namespace std;

class InfixToPostfix
{
	string infix;
	string postfix;
	stack<char> charStack;
	stack<int> intStack;
public:
	InfixToPostfix():infix(""),postfix(""){}
	void setter();
	void getter();
	void convertToPostfix();
	int  precedence(char op);
	void  evaluation();
};

int InfixToPostfix::precedence(char op)
{
	switch (op)
	{
	case '^':
		return 3;
	case '/':
	case '*':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return -1;
	}
}
void InfixToPostfix::setter()
{
	cout << "\n Enter Infix Notation: ";
	getline(cin, infix);
}
void InfixToPostfix::getter()
{
	cout << " Postfix Notation: " << postfix << endl;
}
void InfixToPostfix::convertToPostfix()
{
	int i = 0;
	char ch;

	while (infix[i] != NULL)
	{
		ch = infix[i];
		i++;

		if (isalpha(ch) || isdigit(ch))
			postfix.append(1, ch);
		else if (ch == '(')
			charStack.push(ch);
		else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^')
		{
			if (charStack.empty() || charStack.top() == '(')
				charStack.push(ch);
			else if (precedence(ch) > precedence(charStack.top()))
				charStack.push(ch);
			else
			{
				while (precedence(ch) <= precedence(charStack.top()))
				{
					postfix.append(1, charStack.top());
					charStack.pop();
					if (charStack.empty())
						break;
				}
				charStack.push(ch);

			}
		}
		else if (ch == ')')
		{
			while (charStack.top() != '(' && (!charStack.empty()))
			{
				postfix.append(1, charStack.top());
				charStack.pop();
			}
			charStack.pop();
		}

	}
	while (!charStack.empty()) 
	{
		postfix.append(1, charStack.top());
		charStack.pop();
	}

}
void InfixToPostfix::evaluation()
{
	int i = 0;
	char ch;
	while (postfix[i] != NULL)
	{
		ch = postfix[i];
		i++;
		if (isdigit(ch))
			intStack.push(ch - '0');
		else {
			int operand_2 = intStack.top();
			intStack.pop();
			int operand_1 = intStack.top();
			intStack.pop();

			switch (ch)
			{
			case '+':
				intStack.push(operand_1 + operand_2);
				break;
			case '-':
				intStack.push(operand_1 -operand_2);
				break;
			case '*':
				intStack.push(operand_1 * operand_2);
				break;
			case '/':
				intStack.push(operand_1 / operand_2);
				break;
			case '^':
				intStack.push(pow(operand_1,operand_2));
				break;
			}

		}
		
	}
	cout << " After Evaluation: " << intStack.top() << endl;
	intStack.pop();
}
int main()
{
	InfixToPostfix obj;
	obj.setter();
	obj.convertToPostfix();
	obj.getter();
	obj.evaluation();
}



