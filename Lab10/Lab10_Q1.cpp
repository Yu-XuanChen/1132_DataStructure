#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY = NULL; // 用 NULL 代表沒有節點
class TreeNode {
public:
    int value;// 節點值
    TreeNode* left;// 左子節點
    TreeNode* right;// 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//初始化節點
};

class BinaryTree {
public:
    TreeNode* root;// 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) {// 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;//建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]);// 建立根節點 (陣列第一個元素)
        q.push(&root);// 將根節點的指標加入queue

        size_t i = 1;// 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);// 添加左子節點
                    q.push(&((*nodePtr)->left));// 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);// 添加右子節點
                    q.push(&((*nodePtr)->right));// 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

	//廣度優先搜尋
    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將左子節點的指標加入queue
        }
    }

	//levelsum
    void LevelSum(int level) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue
		q.push(root); // 將根節點的指標加入queue
		int currentlevel = 0; //當前層數
		int levelSum = 0; //當前層的總和

        while (!q.empty()) {
			int levelSize = q.size();//當前層的節點數量
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* current = q.front(); //取出第一個節點
				q.pop(); //將該節點從queue中刪除

                if (currentlevel == level) { //如果當前曾數等於要查詢的曾數
					levelSum += current->value; //累加總和
                }

				if (current->left) q.push(current->left); //將左子節點的指標加入queue
				if (current->right) q.push(current->right); //將右子節點的指標加入queue
            }
            if (currentlevel == level) {
                cout << "第" << level << "層的總和為: " << levelSum << endl; //輸出當前層的總和
				return; //查詢到結果後結束
            }
			currentlevel++; //層數加1
        }
        cout << "超過樹高" << endl;
    }

    //查詢節點
    void Search(int value) {
		TreeNode* target = nullptr;
		queue<TreeNode*> q;//建立queue
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front(); //取出第一個節點
            q.pop(); //將該節點從queue中刪除
            if (current->value == value) { //如果當前節點的值是要查詢的值
                target = current; //找到節點
                break; //結束查詢
            }
			if (current->left) q.push(current->left); //將左子節點的指標加入queue
			if (current->right) q.push(current->right); //將右子節點的指標加入queue
        }

		if (!target) { //如果沒有找到節點
            cout << "未找到指定節點" << endl; 
            return;
        }
        if (!target->left && !target->right) {//找不到左子樹和右子樹
			cout << "該節點為葉節點，沒有子樹" << endl; 
            return;
        }

        int leftSum = 0;
        int rightSum = 0;
		//計算左子樹和右子樹的總和
        if (target->left) {
            queue<TreeNode*> leftq;
			leftq.push(target->left);
            while (!leftq.empty()) {
                TreeNode* current = leftq.front(); //取出第一個節點
                leftq.pop(); //將該節點從queue中刪除
                leftSum += current->value; //累加總和

				if (current->left) leftq.push(current->left); //將左子節點的指標加入queue
				if (current->right) leftq.push(current->right); //將右子節點的指標加入queue
            }
        }
        if (target->right) {
			queue<TreeNode*> rightq;
			rightq.push(target->right);
            while (!rightq.empty()) {
                TreeNode* current = rightq.front(); //取出第一個節點
                rightq.pop(); //將該節點從queue中刪除
                rightSum += current->value; //累加總和
                if (current->left) rightq.push(current->left); //將左子節點的指標加入queue
                if (current->right) rightq.push(current->right); //將右子節點的指標加入queue
            }
        }
			cout << "左子樹總和: " << leftSum << endl; //輸出左子樹的總和
			cout << "右子樹總和: " << rightSum << endl; //輸出右子樹的總和
		
		//比較左右子樹的總和
        if  (leftSum > rightSum) {
			cout << "左子樹總和較大" << endl;
		}
        else if (leftSum < rightSum) {
            cout << "右子樹總和較大" << endl;
        }
        else {
            cout << "左右子樹總和相等" << endl;
        }
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    //查詢層數
    /*
    int level;
	cout << "請輸入要查詢的層數(從0開始): ";
	cin >> level;
	tree.LevelSum(level);
    */

	//查詢節點
    int value;
	cout << "請輸入要查詢的節點值: ";
	cin >> value;
	tree.Search(value);

    system("pause");
    return 0;
}
