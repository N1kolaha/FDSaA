#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct key
{ //int code;
	long long int number;
};
struct list
{
	list* next;
	int strNum;
	
};
struct Node
{
	key data;
	list* numberInList;
	Node* L;
	Node* R;
	
};
void addlist(list*& head, int n)
{

	list* New_one = new list;
	New_one->strNum = n;
	New_one->next = New_one;

	if (head == nullptr)
	{
		New_one->next = New_one;
		head = New_one;
		return;
	}
	list* cursor = head;
	while (cursor->next != head)
	{
		if (New_one->strNum == cursor->strNum) return;
		cursor = cursor->next;
	}
	cursor->next = New_one;
	New_one->next = head;
	cursor = New_one;
	return;
}




bool findList(list*& head, int data) {
	list* current = head;
	do {
		if (current->strNum == data) {
			return true;
		}
		current = current->next;
	} while (current != head);

	return false;
}




int count(list*& head) {
	int flag = 0;
	list* current = head;
	if (!head)
		return flag;
	do {
		flag++;
		current = current->next;
	} while (current != head);
	return flag;
}

void outputlist(list* head, ofstream& file)
{
	list* H = head;
	if (head == nullptr)
	{
		return;
	}
	if (H->next == head)
	{
		file << "- (" << H->strNum << " )";
	}
	else
	{
		file << "- (";
		do
		{

			file << H->strNum << " ";
			H = H->next;

		} while (H != head);
		file << " )";
	}

}


void deleteInList(list*& head, int data) {
	list* Pflag1;
	list* Pdel;


	if (head != nullptr) {
		if (data == head->strNum) {
			Pflag1 = head;
			while (Pflag1->next != head) {
				Pflag1 = Pflag1->next;
			}
			Pflag1->next = head->next;
			delete (head);
			head = Pflag1;
		}
		else {
			Pflag1 = head;
			Pdel = head->next;
			while (Pdel->strNum != data) {
				Pdel = Pdel->next;
				Pflag1 = Pflag1->next;
			}
			Pflag1->next = Pdel->next;
			delete(Pdel);
		}
	}
	else {
		std::cout << "Список пуст или не создан" << std::endl;
	}
}


void printlist(list* head)
{
	list* H = head;
	if (head == nullptr)
	{
		return;
	}
	if (H->next == head)
	{
		cout << "- (" << H->strNum<<" )";
	}
	else
	{
		cout << "- (";
		do
		{
			cout  << H->strNum << " ";
			H = H->next;
			
		} 
		while (H != head);
		cout << " )";
	}
	
}





void deleteListElements(list*& head)
{
	if (head == nullptr)
	{
		//cout << "list deleted" << endl;
		//head = nullptr;
		return;
	}

	list* cursor = head->next;
	//list* current = head;
	//cursor = cursor->next;
	while (cursor != head) {
		list* next = cursor->next;
	delete(cursor);
	cursor = next;
}
	delete head;
	head = nullptr;

}





void add(Node*& head,  long long int number, int strNum)
{
	Node* New_one = new Node;
	Node* cursor = head;
	if (head == nullptr)
	{
		
		New_one->data.number = number;
		New_one->L = nullptr;
		New_one->R = nullptr;
	
		head = New_one;
		New_one->numberInList = nullptr;
		addlist((New_one->numberInList), strNum);
		return;
	}
	else 
	while (cursor!=nullptr) {
		if (cursor->data.number == number) {
			addlist((cursor->numberInList), strNum);
			return;



		}
		if  (cursor->data.number >= number)
		{

			if (cursor->L == nullptr)
			{
				if  (cursor->data.number == number)
				{	
					addlist((cursor->numberInList), strNum);
					return;
				}
				else
				{
					cursor->L = New_one;
					New_one->data.number = number;
					New_one->L = nullptr;
					New_one->R = nullptr;
					
					cursor = cursor->L->L;
					New_one->numberInList = nullptr;
					addlist((New_one->numberInList), strNum);
					return;
				}
			}
			else
				cursor = cursor->L;
		}
		else if  (cursor->data.number <= number)
		{
			if (cursor->R == nullptr)
			{
				if (cursor->data.number == number)
				{
					addlist((cursor->numberInList), strNum);
					return;
				}
				else
				{
					cursor->R = New_one;
					New_one->data.number = number;
					New_one->L = nullptr;
					New_one->R = nullptr;
					
					cursor = cursor->R->R;
					New_one->numberInList = nullptr;
					addlist((New_one->numberInList), strNum);
					return;
				}
			}
			else
				cursor = cursor->R;
		}
	}
}	





void delMaxLeft(Node*& node, Node*& q) {
	if (node->R != nullptr) {
		delMaxLeft(node->R, q);
		
	}
	else {
		q->data = node->data;
		q->numberInList = node->numberInList;
		q = node;
		node = node->L;
		
	}
}

void deleteNode(Node*& root, long long k, int nomer) {
	if (!root) return;

	if (k < root->data.number) {
		deleteNode(root->L, k, nomer);
		
	}
	else if (k > root->data.number) {
		deleteNode(root->R, k, nomer);
		
	}
	else {
		if (findList(root->numberInList, nomer) == true) {
			if (count(root->numberInList) == 1) { 
				Node* q = root;
				if (q->R == nullptr) {
					root = q->L;
					
				}
				else if (q->L == nullptr) {
					root = q->R;
					
				}
				else {
					delMaxLeft(q->L, q); 
					
				}
			}
			else {
				deleteInList(root->numberInList, nomer);
				
			}
		}
		
	}
}


void printTree (Node* head)
{
	if (head != nullptr)
	{
		printTree(head->R);
		cout << head->data.number << ' '; printlist(head->numberInList); cout << endl;
		cout << endl;
		printTree(head->L);
	}
	else
	{
		return;
	}

}
void Obhod(Node* head, ofstream& file)
{
	if (head != nullptr) {
		Obhod(head->L, file);
		Obhod(head->R, file);
		list* current = head->numberInList;
		do {
			file << head->data.number << endl;
			current = current->next;
		} while (current != head->numberInList);
	}
}



void input(Node*& head, ifstream& file)
{
	long long int number;
	int i = 1;
	std::string str;


	while (!file.eof()) {
		std::getline(file, str, '\n');
		{
			number = std::stoll(str);
			add(head, number, i);
			i++;
		}
	}
}

void output(Node* head, ofstream& file)
{
	if (head != nullptr)
	{
		output(head->R,file);
		file << head->data.number << ' '; outputlist(head->numberInList,file); cout << endl;
		file << endl;
		output(head->L,file);
	}
	else
	{
		return;
	}

}


void deleteAllTree(Node* &head) {
	if (head!=nullptr) {
		
		deleteAllTree(head->L);
		deleteAllTree(head->R);
		deleteListElements(head->numberInList);
		delete head;
		head = nullptr;
	}
	
}


void Draw(Node* root, int h) {
	if (root != nullptr) {
		Draw(root->R, h + 4);
		for (int i = 1; i <= h; i++) {
			std::cout << " ";
		}
		std::cout << root->data.number << " ";  printlist(root->numberInList); std::cout << std::endl;
		Draw(root->L, h + 4);
	}
}

int main()
{
	Node* Head = nullptr;
	//std::ifstream iFile("input.txt");
	//std::ofstream oFile("output.txt");
	//input(Head, iFile);
	//printTree(Head);
	//deleteNode(Head, 9240000005, 1);
	//printTree(Head);
	////deleteAllTree(Head);
	//printTree(Head);
	//output(Head, oFile);
	//oFile.close();

	for (int i = 0; i < 5; i++)
		add(Head, 9240000005 + i, i + 1);
	//for (int i = 0; i < 5; i++)
		//add(Head, 9230000000 + i, i + 1);
	//for (int i = 5; i <10; i++)
	//add(Head, 9230000005 + i, i + 1);
//add(Head, 9240000006, 10);
//add(Head, 9240000006, 11);
//add(Head, 9240000006, 41);

//add(Head, 9240000004, 228);
//add(Head, 9240000005, 229);
////add(Head, 9240000006, 7);
//add(Head, 9240000005, 1);
//
//deleteNode(Head, 9240000006, 2);
//deleteAllTree(Head);
//deleteNode(Head, 9230000004, 5);
//deleteNode(Head, 9230000003, 4);
//deleteNode(Head, 9240000005, 229);
	//Head=deleterNode(Head, 9240000006, 10);
	//deleteNode(Head, 9240000005, 1);
	//add(Head, 9230000005 , 10);
	//add(Head, 9230000005, 10);
	//add(Head, 9240000005, 10);
	//deleteNode(Head, 9230000014, 10);
	//deleteAllTree(Head);
	
	Draw(Head,0);
	

	//cout << endl;
	//deleteNode(Head, 9240000005, 1);
	////deleteNode(Head, 9240000005, 21);
	//printTree(Head);
	//cout << endl;
	//deleteAllTree(Head);
	//printTree(Head);
	//cout << endl;
	//for (int i = 20; i > 0; i--)
	//	add(Head, 9240000020 - i, 21 - i);
	//cout << endl;
	//printTree(Head);
	//for (int i = 20; i > 0; i--)
	//	deleteNode(Head, 9240000020 - i, 21 - i);
	//cout << endl;
	//printTree(Head);
	
}

