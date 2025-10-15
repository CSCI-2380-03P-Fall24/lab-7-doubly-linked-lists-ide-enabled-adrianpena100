	#include "StudentList.h"
	#include <iostream>
	using namespace std;

	// Define a constructor to initialize the list. The list starts with no Students
	StudentList::StudentList() {
		head = nullptr;             // initialize head to null
		tail = nullptr;             // initialize tail to null
		numStudents = 0;            // list starts empty
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;         // return count
	}

	// add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* n = new Node(s, head, nullptr);   // new node before head
		if (head != nullptr) {
			head->prev = n;                     // link old head back to new node
		}
		head = n;                               // move head to new node
		if (tail == nullptr) {
			tail = n;                           // if empty, tail also becomes new node
		}
		numStudents++;                          // increase size
	}

	// add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node* n = new Node(s, nullptr, tail);   // new node after tail
		if (tail != nullptr) {
			tail->next = n;                     // link old tail forward to new node
		}
		tail = n;                               // move tail to new node
		if (head == nullptr) {
			head = n;                           // if empty, head also becomes new node
		}
		numStudents++;                          // increase size
	}

	// Print out the names of each student in the list.
	void StudentList::printList() {
		Node* cur = head;                       // start from head
		bool first = true;                      // track spacing
		while (cur != nullptr) {
			if (!first) {
				cout << " ";                    // space between names
			}
			cout << cur->data.name;             // print student name
			first = false;                      // mark first print done
			cur = cur->next;                    // move to next node
		}
		cout << endl;                           // finish with newline
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if (tail == nullptr) {
			cout << "Cannot popBack: list is empty" << endl;
			return;                             // no node to remove
		}
		Node* temp = tail;                      // store node to delete
		tail = tail->prev;                      // move tail back
		if (tail != nullptr) {
			tail->next = nullptr;               // disconnect deleted node
		} else {
			head = nullptr;                     // list became empty
		}
		delete temp;                            // free memory
		numStudents--;                          // decrease size
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if (head == nullptr) {
			cout << "Cannot popFront: list is empty" << endl;
			return;                             // no node to remove
		}
		Node* temp = head;                      // store node to delete
		head = head->next;                      // move head forward
		if (head != nullptr) {
			head->prev = nullptr;               // disconnect deleted node
		} else {
			tail = nullptr;                     // list became empty
		}
		delete temp;                            // free memory
		numStudents--;                          // decrease size
	}

	// insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For example, Node with student at index i, becomes index i+1"
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if (index <= 0) {
			addFront(s);                        // insert at front
			return;
		}
		if (index >= numStudents) {
			cout << "Index out of range; inserting at back" << endl;
			addBack(s);                         // insert at back
			return;
		}

		Node* cur = head;                       // start at head
		for (int i = 0; i < index; i++) {
			cur = cur->next;                    // move to target position
		}
		Node* n = new Node(s, cur, cur->prev);  // new node before cur
		cur->prev->next = n;                    // link previous to new
		cur->prev = n;                          // link current back to new
		numStudents++;                          // increase size
	}

	// find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		Node* cur = head;                       // start from head
		while (cur != nullptr) {
			if (cur->data.id == idNum) {
				return cur->data;               // return match
			}
			cur = cur->next;                    // continue searching
		}
		cout << "Student with id " << idNum << " not found" << endl;
		Student dummy;                          // default dummy
		return dummy;                           // return dummy if not found
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		Node* cur = head;                       // start at head
		while (cur != nullptr && cur->data.id != idNum) {
			cur = cur->next;                    // look for id
		}
		if (cur == nullptr) {
			cout << "No student with id " << idNum << " to remove" << endl;
			return;
		}

		if (cur->prev != nullptr) {
			cur->prev->next = cur->next;        // link around node
		} else {
			head = cur->next;                   // node is head
		}

		if (cur->next != nullptr) {
			cur->next->prev = cur->prev;        // link around node
		} else {
			tail = cur->prev;                   // node is tail
		}
		delete cur;                             // delete node
		numStudents--;                          // decrease size
	}

	// Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node* cur = head;                       // start from head
		while (cur != nullptr) {
			if (cur->data.id == idNum) {
				cur->data.GPA = newGPA;         // update GPA if match found
				return;
			}
			cur = cur->next;                    // move to next
		}
	}

	// Add all students from otherList to this list.
	// otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the current list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if (otherList.numStudents == 0) {
			return;                             // nothing to merge
		}
		if (numStudents == 0) {
			head = otherList.head;              // take other's chain
			tail = otherList.tail;
			numStudents = otherList.numStudents;
		} else {
			tail->next = otherList.head;        // link lists
			otherList.head->prev = tail;
			tail = otherList.tail;              // update tail
			numStudents += otherList.numStudents;
		}
		otherList.head = nullptr;               // empty other list
		otherList.tail = nullptr;
		otherList.numStudents = 0;
	}

	// create a StudentList of students whose gpa is at least minGPA.
	// Return this list.  The original (current) list should
	// not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList result;                     // new list
		Node* cur = head;                       // start from head
		while (cur != nullptr) {
			if (cur->data.GPA >= minGPA) {
				result.addBack(cur->data);      // add qualifying student
			}
			cur = cur->next;                    // move to next
		}
		return result;                          // return filtered list
	}

	// remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {
		if (head == nullptr) {
			cout << "List is empty — nothing to remove" << endl;
			return;
		}
		Node* cur = head;                       // start at head
		while (cur != nullptr) {
			Node* nextNode = cur->next;         // store next before deletion
			if (cur->data.GPA < threshold) {
				if (cur->prev != nullptr) {
					cur->prev->next = cur->next; // unlink from prev
				} else {
					head = cur->next;             // move head if deleting first node
				}

				if (cur->next != nullptr) {
					cur->next->prev = cur->prev; // unlink from next
				} else {
					tail = cur->prev;             // move tail if deleting last node
				}
				delete cur;                       // free memory
				numStudents--;                    // decrease size
			}
			cur = nextNode;                       // move to next node
		}
	}
