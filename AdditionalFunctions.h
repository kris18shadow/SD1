#include <iostream>
#include "Header.h"

bool isDigit(char x)
{
	return (x >= 0 && x <= 9);
}

bool isOperation(char x)
{
	return (x >= 'A' && x <= 'z');
}

bool isBracket(char x)
{
	return (x == '(' || x == ')');
}

//Operation info structure:
struct operInfo
{
	char identificator;
	char action;
	int priority;
	int associativity;
};

//evaluating precedence:
int precedence(char input, operInfo* opFromFile)
{
	bool found = false;
	int count = 0;

	while(!found)
	{
		if(input == opFromFile[count].action)
		{
			return opFromFile[count].priority;
			found = true;
		}
		else
			count++;
	}

	return 0;
}

//Convert expression into postfix expression:
bool  convertExpr(const char* expr, char* rpn, operInfo* FromFile)
{
  Stack<char> op;
  while(*expr)
  {
     if(isDigit(*expr))
	 {
	    *rpn = *expr;
		++rpn;
	 }
	 else if(*expr == '(')
	 {
	    op.push(*expr);
	 }
	 else if(*expr == ')')
	 {
	   char curOp;
	   while(!op.isEmpty())
	   {
	     curOp = op.peek();
		 if(curOp == '(')
		 {
		   *rpn = curOp;
		   ++rpn; 
		 }
		 else 
		 {
		   op.pop();
		   break;
		 }
	   }
	 }
	 else if(isOperation(*expr))
	 {
	    bool lowerPrecedence = false;
	    char curOp;
		while(!op.isEmpty() && !lowerPrecedence)
		{
		  curOp = op.peek();
		  if(precedence(curOp, FromFile) >= precedence(*expr, FromFile))
		  {
		    *rpn = curOp;
			++rpn;
			op.pop();
		  }
		  else lowerPrecedence = true;
		}
		 op.push(*expr);
	}
	else
	{
	  std::cerr << "Invalid token";
	  return false;
	}
	 ++expr;
  }

  while(!op.isEmpty())
  {
    char curOp = op.peek();
	if(curOp == '(')
	{
	  std::cerr << "Invalid token";
	  return false;
	}
	*rpn = curOp;
	++rpn;
	op.pop();
	*rpn='\0';
	return true;
  }
  return false; 
}

//Calculating the converted postfix expression:
double calculate(const char * str, operInfo* FromFile) 
{ 
    Stack<double> stack;
    while (*str) 
	{
        if (*str >= '0' && *str <= '9') 
		{
            stack.push(*str - '0');
        }
        else if (isOperation(*str)) 
		{
            if (stack.getLength() != 2) 
			{
                std::cerr << "Incorrect expression";
            }

            double x = stack.peek();
			stack.pop();
            double y = stack.peek();
			stack.pop();
			
			bool found = false;
			int count = 0;
			int associativity;
			char op;

			while(!found)
	        {
		       if(*str == FromFile[count].identificator)
		       {
				 op = FromFile[count].action;
			     associativity = FromFile[count].associativity;
			     found = true;
		       }
		       else
			     count++;
	        }

			if(associativity = 0)
			{
               switch (op)
               {
                case '+':
                  stack.push(x + y);
                  break;
                case '-':
                  stack.push(y - x);
                  break;
                case '*':
                  stack.push(x * y);
                  break;
                case '/':
                  stack.push(y / x);
                  break;
               }
			}
			else
			{
				switch (op)
               {
                case '+':
                  stack.push(y + x);
                  break;
                case '-':
                  stack.push(x - y);
                  break;
                case '*':
                  stack.push(y * x);
                  break;
                case '/':
                  stack.push(x / y);
                  break;
               }
			}
        }
        ++str;
    }
 
    if (stack.getLength() != 1) 
	{
        std::cerr <<"Incorrect expression";
    }

    return stack.peek();
}

//Reading operation info from file to array of operInfo structures:
void readTo(std::fstream& is, operInfo* opFromFile )
{
	if(is.good())
	{
	  char* buffer = new char[10];
   	 
	  int count = 0;
	  while(!is.eof())
	  {
		 is.getline(buffer,10);
	     opFromFile[count].identificator = buffer[0];
		 opFromFile[count].action = buffer[2];
		 opFromFile[count].priority = atoi(strcat(&buffer[4], &buffer[5]));
		 opFromFile[count].associativity = atoi(strcat(&buffer[7], &buffer[8]));
		 count++;
	  }

	}
	else
		std::cerr << "File is bad!";
}

bool openBrace(char x)
{
	return '(' == x;
}

bool closeBrace(char x)
{
	return ')' == x;
}

//Validate the expression:
bool isValid(const char* expression)
{
	Stack<char> st;
	while(*expression)
	{
		if(openBrace(*expression))
			st.push(*expression);
		else 
		if(closeBrace(*expression))
		{
			if(st.isEmpty())
				return false;

			char open = st.peek();
			if( open == *expression)
				st.pop();
			else 
				return false;
		}
	}

	expression++;
	return st.isEmpty();
}