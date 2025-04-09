#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
public:
    Stack() { top = nullptr; } // 初始化堆疊

    // Push 操作：將元素放入堆疊
	void push(char ch) {
		Node* newNode = new Node; //建立新的node
		newNode->data = ch;  //將字元放進node
		newNode->next = top; //將新node的next指向原本的top
		top = newNode; //top改成新的node

    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
		char poppedch = top->data; //poppedch為最頂端的字元
		Node* temp = top; //temp暫存頂端的node
		top = top->next; // top改為下一個node
		delete temp; //刪除temp
		return poppedch; //回傳poppedch
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
		if (top != nullptr) { //如果top不是空的
			return top->data; //回傳top的字元
        }
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
		return (top == nullptr); //如果top是空的，回傳true
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
    switch (op) {
	case'+': case'-': //如果是加法或減法
		return 1; // 傳回1
	case'*': case'/': //如果是乘法或除法
		return 2; // 傳回2
	default:
		return 0; // 如果不是運算子，則傳回0
    }
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
	Stack stack; // 建立Stack
    int i = 0, j = 0;

    while (infix[i] != '\0') {
		char current = infix[i];
		if (isalnum(current)) { //如果遇到數字
			postfix[j++] = current; //放入後序
		}
		else if (current == '(') { //如果遇到左括號
			stack.push(current); //推入stack
		}
		else if (current == ')') { //如果遇到右括號
			while (!stack.isEmpty() && stack.peek() != '(') {  //檢查是不是空的以及stack最頂端是不是左括號
				postfix[j++] = stack.pop(); //將stack最頂端的pop，然後放入後序
			}
			stack.pop(); // 移除左括號
		}
		else { // 如果遇到運算子
			while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(current)) { //檢查stack是不是空的，然後stack最頂端的優先順序是不是大於等於現在運算子的優先順序
				postfix[j++] = stack.pop(); //將stack最頂端的pop，然後放入後序
			}
			stack.push(current); // 將運算子推入stack
		}

		i++; // 移動到下一個數字
    }
	while (!stack.isEmpty()) { //如果stack不為空
		postfix[j++] = stack.pop(); //將stack剩下的放入後序
	}
	postfix[j] = '\0';
	
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}
