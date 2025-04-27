#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
//Using BST node structure
//Course structure for each course
struct Course {
	string courseId;
	string courseName;
	vector <string> prereq;
};

//Node structure
struct Node {
	//Basic node structure
	Course course;
	Node* left;
	Node* right;

	//Constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}
	//course initialization
	Node(Course initCourse) {
		course = initCourse;
	}
};

//BST Class declaration

class BinarySearchTree {
private:
	Node* root;
	void addNode(Node* node, Course course);		//Method to add a node
	void inOrderTraversal(Node* node);				//Method to traverse the tree in order

public:
	BinarySearchTree();				//Constructor	
	virtual ~BinarySearchTree(); //Destructor
	void Insert(Course course); //Method to insert a course
	void inOrder(); //Method to call inOrderTraversal
	Course search(string courseId); //Method to search for a course
};

//Default Constructor
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}
//Destructor
BinarySearchTree::~BinarySearchTree() {
	delete root;
}

//Method to insert a course
void BinarySearchTree::Insert(Course course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		addNode(root, course);
	}
}

//Method to add a node
void BinarySearchTree::addNode(Node* node, Course course) {
	//Go left if courseId is less than the current node's courseId
	if (course.courseId < node->course.courseId) {
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		else {
			addNode(node->left, course);
		}
	}
	//Go right if courseId is greater than the current node's courseId
	else if (course.courseId > node->course.courseId) {
		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		else {
			addNode(node->right, course);
		}
	}
	//If courseId is equal, do nothing
	else {
		cout << "Course ID already exists: " << course.courseId << endl;
	}
}

//Function to print a course
void printCourse(const Course& course) {
	cout << "Course ID: " << course.courseId << endl;
	cout << "Course Name: " << course.courseName << endl;
	cout << "Prerequisites: ";
	for (const string& prereq : course.prereq) {
		cout << prereq << " ";
	}
	cout << endl;
}
//Method to traverse the tree in order
void BinarySearchTree::inOrderTraversal(Node* node) {
	if (node != nullptr) {
		inOrderTraversal(node->left);
		printCourse(node->course);
		inOrderTraversal(node->right);
	}
}
//Method to call inOrderTraversal
void BinarySearchTree::inOrder() {
	inOrderTraversal(root);
}

//Method to search for a course
Course BinarySearchTree::search(string courseId) {
	Node* current = root;
	while (current != nullptr) {
		if (courseId == current->course.courseId) {
			return current->course;
		}
		else if (courseId < current->course.courseId) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	Course emptyCourse;
	return emptyCourse; // Return an empty course if not found
}

//Function to read the course data from a file
void readCourseData(const string& filename, BinarySearchTree& bst) {
	ifstream inFile;
	inFile.open(filename);
	if (!inFile.is_open()) {
		cerr << "Error opening file: " << filename << endl;
		return;
	}
	string line;
	while (getline(inFile, line)) {
		istringstream iss(line);
		Course course;
		getline(iss, course.courseId, ',');
		getline(iss, course.courseName, ',');
		string prereq;
		while (getline(iss, prereq, ',')) {
			course.prereq.push_back(prereq);
		}
		bst.Insert(course);
	}
	cout << "Data loaded successfully." << endl;
	// Close the file
	inFile.close();
}

//Function to display the menu
void displayMenu() {
	cout << "Menu:" << endl;
	cout << "1. Load Data Structure" << endl;
	cout << "2. Print Course List" << endl;
	cout << "3. Print Course" << endl;
	cout << "9. Exit" << endl;
	cout << "Enter your choice: ";
}

//Function to print the course list
void printCourseList(BinarySearchTree& bst) {
	cout << "Course List:" << endl;
	bst.inOrder();
}

//Main function
int main() {
	BinarySearchTree bst;
	int choice;
	string filename = "CS 300 ABCU_Advising_Program_Input.csv"; 
	while (true) {
		displayMenu();
		cin >> choice;
		switch (choice) {
		case 1:
			readCourseData(filename, bst);
			break;
		case 2:
			printCourseList(bst);
			break;
		case 3: {
			string courseId;
			cout << "Enter Course ID: ";
			cin >> courseId;
			Course course = bst.search(courseId);
			if (course.courseId.empty()) {
				cout << "Course not found." << endl;
			}
			else {
				printCourse(course);
			}
			break;
		}
		case 9:
			return 0;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	}
	return 0;

}