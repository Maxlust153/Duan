#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

struct DuAn {
    string MaDuAn, TenDuAn;
    int Von;
};

struct Node {
    DuAn data;
    Node *next;
    Node *pre;
};

struct doubleList {
    Node *head;
    Node *tail;
};

void initialize(doubleList &list) {
    list.head = NULL;
    list.tail = NULL;
}

Node *createNode(DuAn d) {
    Node *pNode = new Node;
    pNode->data = d;
    pNode->next = NULL;
    pNode->pre = NULL;
    return pNode;
}

// 1. Nhap thong tin du an
DuAn inputDuAn() {
    DuAn d;
    cout << "Nhap ma du an: ";
    cin >> d.MaDuAn;
    cout << "Nhap ten du an: ";
    cin.ignore();
    getline(cin, d.TenDuAn);
    cout << "Nhap von du an: ";
    cin >> d.Von;
    return d;
}

// 2. Them dau
void insertFirst(doubleList &list, DuAn d) {
    Node *pNode = createNode(d);
    if (list.head == NULL) {
        list.head = pNode;
        list.tail = pNode;
    } else {
        pNode->next = list.head;
        list.head->pre = pNode;
        list.head = pNode;
    }
}

// 3. Them cuoi
void insertLast(doubleList &list, DuAn d) {
    Node *pNode = createNode(d);
    if (list.tail == NULL) {
        list.head = pNode;
        list.tail = pNode;
    } else {
        pNode->pre = list.tail;
        list.tail->next = pNode;
        list.tail = pNode;
    }
}

// 4. Chen giua
void insertMid(doubleList &list, DuAn d, int pos) {
    if (pos == 0 || list.head == NULL) {
        insertFirst(list, d);
    } else {
        Node *p = list.head;
        int currentPos = 0;
        while (p != NULL && currentPos < pos - 1) {
            p = p->next;
            currentPos++;
        }
        if (p != NULL && p->next != NULL) {
            Node *pNode = createNode(d);
            pNode->next = p->next;
            pNode->pre = p;
            p->next->pre = pNode;
            p->next = pNode;
        } else {
            insertLast(list, d);
        }
    }
}

// 5. Xoa dau
void deleteFirst(doubleList &list) {
    if (list.head == NULL) {
        cout << "DS Rong." << endl;
        return;
    }

    Node *p = list.head;
    list.head = list.head->next;

    if (list.head != NULL) {
        list.head->pre = NULL;
    } else {
        list.tail = NULL;
    }

    delete p;
    cout << "Da xoa du an dau danh sach." << endl;
}

// 6. Xoa cuoi
void deleteLast(doubleList &list) {
    if (list.tail == NULL) {
        cout << "DS Rong." << endl;
        return;
    }

    Node *p = list.tail;
    list.tail = list.tail->pre;

    if (list.tail != NULL) {
        list.tail->next = NULL;
    } else {
        list.head = NULL;
    }

    delete p;
    cout << "Da xoa du an cuoi danh sach." << endl;
}
// 7. Xoa du an theo ma du an
void deleteByMaDuAn(doubleList &list, string maDuAn) {
    Node *p = list.head;
    while (p != NULL && p->data.MaDuAn != maDuAn) {
        p = p->next;
    }

    if (p == NULL) return;

    if (p->pre != NULL) {
        p->pre->next = p->next;
    } else {
        list.head = p->next;
    }

    if (p->next != NULL) {
        p->next->pre = p->pre;
    } else {
        list.tail = p->pre;
    }

    delete p;
}

// 8. Xoa du an theo ten du an
void deleteByTenDuAn(doubleList &list, string tenDuAn) {
    Node *p = list.head;
    while (p != NULL && p->data.TenDuAn != tenDuAn) {
        p = p->next;
    }

    if (p == NULL) return;

    if (p->pre != NULL) {
        p->pre->next = p->next;
    } else {
        list.head = p->next;
    }

    if (p->next != NULL) {
        p->next->pre = p->pre;
    } else {
        list.tail = p->pre;
    }

    delete p;
}

// 9. xoa nhung du an co von nho hon 1 so
void deleteProjectsUnderMinVon(doubleList &list, int minVon) {
    Node *current = list.head;
    Node *temp;

    while (current != NULL) {
        if (current->data.Von < minVon) {
            if (current == list.head) {
                list.head = current->next;
                if (list.head != NULL)
                    list.head->pre = NULL;
                delete current;
                current = list.head;
            } else if (current == list.tail) {
                list.tail = current->pre;
                list.tail->next = NULL;
                delete current;
                current = NULL;
            } else {
                temp = current;
                current->pre->next = current->next;
                current->next->pre = current->pre;
                current = current->next;
                delete temp;
            }
        } else {
            current = current->next;
        }
    }
}

// 10. Xoa cac du an co von lon hon 1 so
void deleteProjectsGreaterThan(doubleList &list, int threshold) {
    Node *current = list.head;

    while (current != NULL) {
        if (current->data.Von > threshold) {
            Node *toDelete = current;

            if (current->pre != NULL) {
                current->pre->next = current->next;
            } else {
                // If deleting the head
                list.head = current->next;
            }

            if (current->next != NULL) {
                current->next->pre = current->pre;
            } else {
                // If deleting the tail
                list.tail = current->pre;
            }

            current = current->next;
            delete toDelete;
        } else {
            current = current->next;
        }
    }
}

// 11. Xoa nhung du an co von trong khoang
void deleteProjectsInRange(doubleList &list, int minVon, int maxVon) {
    Node *p = list.head;
    while (p != NULL) {
        Node *nextNode = p->next;
        if (p->data.Von >= minVon && p->data.Von <= maxVon) {
            if (p->pre != NULL) {
                p->pre->next = p->next;
            } else {
                list.head = p->next;
            }
            if (p->next != NULL) {
                p->next->pre = p->pre;
            } else {
                list.tail = p->pre;
            }
            delete p;
        }
        p = nextNode;
    }
}

// 12.xoa toan bo du an trong danh sach
void deleteAllProjects(doubleList &list) {
    Node *current = list.head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    list.head = NULL;
    list.tail = NULL;
}

// 13. In danh sach du an
void printList(const doubleList &list) {
    Node *p = list.head;
    cout <<"|"<< setw(10) << left<< "Ma Du An" <<"|"<< setw(20) << "Ten Du An" <<"|"<< setw(10) << "Von" <<"|"<< endl;
    while (p != NULL) {
        cout <<"|"<< setw(10) << left<< p->data.MaDuAn <<"|"<< setw(20) << p->data.TenDuAn <<"|"<< setw(10) << p->data.Von <<"|"<< endl;
        p = p->next;
    }
}

// 14. Tim du an co so von lon hon 1 so
void searchProjects(doubleList list, int threshold) {
    Node *temp = list.head;
    while (temp != NULL) {
        if (temp->data.Von > threshold) {
            cout << "Ma Du An: " << temp->data.MaDuAn << ", Ten Du An: " << temp->data.TenDuAn << ", Von: " << temp->data.Von << endl;
        }
        temp = temp->next;
    }
}

// 15. Tim du an co so von nho hon 1 so
void searchProjectsUnderThreshold(doubleList list, int threshold) {
    Node *temp = list.head;
    bool found = false;
    while (temp != NULL) {
        if (temp->data.Von < threshold) {
            cout << "Ma Du An: " << temp->data.MaDuAn << ", Ten Du An: " << temp->data.TenDuAn << ", Von: " << temp->data.Von << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "Khong co du an nao co von nho hon " << threshold << "." << endl;
    }
}

// 16. tim du an trong khoang 
void findProjectsInRange(doubleList list, int minVon, int maxVon) {
    Node *current = list.head;
    bool found = false;

    while (current != NULL) {
        if (current->data.Von >= minVon && current->data.Von <= maxVon) {
            found = true;
            cout << "Ma du an: " << current->data.MaDuAn << endl;
            cout << "Ten du an: " << current->data.TenDuAn << endl;
            cout << "Von: " << current->data.Von << endl << endl;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Khong tim thay du an nao trong khoang von yeu cau." << endl;
    }
}

// 17. Tim du an theo ma du an
void searchProjectByID(doubleList list, string maDuAn) {
    Node *temp = list.head;
    while (temp != NULL) {
        if (temp->data.MaDuAn == maDuAn) {
            cout << "Tim thay: Ma Du An: " << temp->data.MaDuAn << ", Ten Du An: " << temp->data.TenDuAn << ", Von: " << temp->data.Von << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Du An ung voi Ma Du An " << maDuAn << " khong ton tai." << endl;
}

// 18. Tim du an theo ten du an
void searchProjectByName(doubleList list, string tenDuAn) {
    Node *temp = list.head;
    while (temp != NULL) {
        if (temp->data.TenDuAn == tenDuAn) {
            cout << "Tim thay: Ma Du An: " << temp->data.MaDuAn << ", Ten Du An: " << temp->data.TenDuAn << ", Von: " << temp->data.Von << endl;
        }
        temp = temp->next;
    }
    cout << "Du An co ten " << tenDuAn << " khong ton tai." << endl;
}

// 19. sap xep du an theo von tang dan 
void sortByVonAscending(doubleList &list) {
    if (list.head == NULL || list.head->next == NULL) {
        return;
    }
    Node *current = list.head;
    Node *index = NULL;
    DuAn temp;

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            // Neu gia tri von cua node hien thi lon hon giá tri von cua node index
            if (current->data.Von > index->data.Von) {
                // Hoán doi du lieu giua 2 node
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

// 20.sap xep du an theo von giam dan 
void sortByVonDescending(doubleList &list) {
    if (list.head == NULL || list.head->next == NULL) {
        // Danh sách rong or chi có mot ph?n tu, không can sap xep
        return;
    }

    Node *current = list.head;
    Node *index = NULL;
    DuAn temp;

    while (current != NULL) {
        index = current->next;

        while (index != NULL) {
            // Neu gia tri von cua node hien thi nho hon giá tri von cua node index
            if (current->data.Von < index->data.Von) {
                //Hoán doi du lieu giua 2 node
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}
 
 // 21. tinh tong so von cua tat ca du an trong danh sach 
 int calculateTotalCapital(doubleList list) {
    Node *current = list.head;
    int totalCapital = 0;

    while (current != NULL) {
        totalCapital += current->data.Von;
        current = current->next;
    }

    return totalCapital;
}

// 22. Dem so du an trong danh sach
int countProjects(doubleList list) {
    Node *current = list.head;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

// 23. tinh trung binh von cua tat ca cac du an 
float calculateAverageCapital(doubleList list) {
    Node *current = list.head;
    int totalCapital = 0;
    int projectCount = 0;

    while (current != NULL) {
        totalCapital += current->data.Von;
        projectCount++;
        current = current->next;
    }

    if (projectCount == 0) {
        // TH du an rong
        return 0;
    }

    // Tính trung bình v0n
    return (totalCapital) / projectCount;
}
// 24.  Them du lieu vao tep
void saveToFile(const doubleList &list, const string &filename) {
    ofstream outFile(filename.c_str());  
    if (!outFile) {
        cout << "Khong the mo tep de ghi du lieu.\n";
        return;
    }
    Node *p = list.head;
    while (p != NULL) {
        outFile << p->data.MaDuAn << "\n" << p->data.TenDuAn << "\n" << p->data.Von << "\n";
        p = p->next;
    }
    outFile.close();
    cout << "Da luu du lieu vao tep " << filename << endl;
}

// 25.  Nap du lieu tu tep
void loadFromFile(doubleList &list, const string &filename) {
    ifstream inFile(filename.c_str());  
    if (!inFile) {
        cout << "Khong the mo tep de doc du lieu.\n";
        return;
    }
    initialize(list);  
    DuAn d;
    while (getline(inFile, d.MaDuAn) && getline(inFile, d.TenDuAn) && (inFile >> d.Von)) {
        inFile.ignore();  
        insertLast(list, d);
    }
    inFile.close();
    cout << "Da nap du lieu tu tep " << filename << endl;
}

// Menu
void menu(doubleList &list) {
    int choice;
    bool exitMenu = false;
    
    while (!exitMenu) {
        cout << "\n========================= MENU ============================" << endl;
        cout << "1. Nhap thong tin du an" << endl;
        cout << "2. Them du an vao dau danh sach" << endl;
        cout << "3. Them du an vao cuoi danh sach" << endl;
        cout << "4. Chen du an vao vi tri bat ky" << endl;
        cout << "5. Xoa du an dau danh sach" << endl;
        cout << "6. Xoa du an cuoi danh sach" << endl;
        cout << "7. Xoa du an theo ma du an" << endl;
        cout << "8. Xoa du an theo ten du an" << endl;
        cout << "9. Xoa nhung du an co von nho hon mot so" << endl;
        cout << "10. Xoa nhung du an co von lon hon mot so" << endl;
        cout << "11. Xoa nhung du an co von trong khoang" << endl;
        cout << "12. Xoa toan bo du an trong danh sach" << endl;
        cout << "13. In danh sach du an" << endl;
        cout << "14. Tim du an co von lon hon mot so" << endl;
        cout << "15. Tim du an co von nho hon mot so" << endl;
        cout << "16. Tim du an trong khoang von" << endl;
        cout << "17. Tim du an theo ma du an" << endl;
        cout << "18. Tim du an theo ten du an" << endl;
        cout << "19. Sap xep danh sach du an theo von tang dan" << endl;
        cout << "20. Sap xep danh sach du an theo von giam dan" << endl;
        cout << "21. Tinh tong so von cua tat ca du an trong danh sach" << endl;
        cout << "22. Dem so du an trong danh sach" << endl;
        cout << "23. Tinh trung binh von cua cac du an trong danh sach" << endl;
        cout << "24. Luu du lieu vao tep" << endl;
        cout << "25. Nap du lieu tu tep" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "\n Nhap lua chon cua ban: ";
        cin >> choice;
        
        switch (choice) {
            case 0:
                exitMenu = true;
                cout << "Thoat chuong trinh." << endl;
                break;
            case 1:
                {
                    DuAn d = inputDuAn();
                    insertLast(list, d);
                    break;
                }
            case 2:
                {
                    DuAn d = inputDuAn();
                    insertFirst(list, d);
                    break;
                }
            case 3:
                {
                    DuAn d = inputDuAn();
                    insertLast(list, d);
                    break;
                }
            case 4:
                {
                    int pos;
                    cout << "Nhap vi tri can chen: ";
                    cin >> pos;
                    DuAn d = inputDuAn();
                    insertMid(list, d, pos);
                    break;
                }
            case 5:
                deleteFirst(list);
                break;
            case 6:
                deleteLast(list);
                break;
            case 7:
                {
                    string maDuAn;
                    cout << "Nhap ma du an can xoa: ";
                    cin >> maDuAn;
                    deleteByMaDuAn(list, maDuAn);
                    break;
                }
            case 8:
                {
                    string tenDuAn;
                    cout << "Nhap ten du an can xoa: ";
                    cin.ignore();
                    getline(cin, tenDuAn);
                    deleteByTenDuAn(list, tenDuAn);
                    break;
                }
            case 9:
                {
                    int minVon;
                    cout << "Nhap so von nho nhat can xoa: ";
                    cin >> minVon;
                    deleteProjectsUnderMinVon(list, minVon);
                    break;
                }
            case 10:
                {
                    int threshold;
                    cout << "Nhap so von lon nhat can xoa: ";
                    cin >> threshold;
                    deleteProjectsGreaterThan(list, threshold);
                    break;
                }
            case 11:
                {
                    int minVon, maxVon;
                    cout << "Nhap gioi han von (min max): ";
                    cin >> minVon >> maxVon;
                    deleteProjectsInRange(list, minVon, maxVon);
                    break;
                }
            case 12:
                deleteAllProjects(list);
                break;
            case 13:
                printList(list);
                break;
            case 14:
                {
                    int threshold;
                    cout << "Nhap so von lon hon: ";
                    cin >> threshold;
                    searchProjects(list, threshold);
                    break;
                }
            case 15:
                {
                    int threshold;
                    cout << "Nhap so von nho hon: ";
                    cin >> threshold;
                    searchProjectsUnderThreshold(list, threshold);
                    break;
                }
            case 16:
                {
                    int minVon, maxVon;
                    cout << "Nhap gioi han von (min max): ";
                    cin >> minVon >> maxVon;
                    findProjectsInRange(list, minVon, maxVon);
                    break;
                }
            case 17:
                {
                    string maDuAn;
                    cout << "Nhap ma du an can tim: ";
                    cin >> maDuAn;
                    searchProjectByID(list, maDuAn);
                    break;
                }
            case 18:
                {
                    string tenDuAn;
                    cout << "Nhap ten du an can tim: ";
                    cin.ignore();
                    getline(cin, tenDuAn);
                    searchProjectByName(list, tenDuAn);
                    break;
                }
            case 19:
                sortByVonAscending(list);
                cout << "Da sap xep danh sach theo von tang dan." << endl;
                break;
            case 20:
                sortByVonDescending(list);
                cout << "Da sap xep danh sach theo von giam dan." << endl;
                break;
            case 21:
                {
                    int totalCapital = calculateTotalCapital(list);
                    cout << "Tong von cua tat ca du an trong danh sach la: " << totalCapital << endl;
                    break;
                }
            case 22:
                {
                    int count = countProjects(list);
                    cout << "Tong so du an trong danh sach la: " << count << endl;
                    break;
                }
            case 23:
                {
                    float averageCapital = calculateAverageCapital(list);
                    cout << "Trung binh von cua cac du an trong danh sach la: " << averageCapital << endl;
                    break;
                }
            case 24:
                {
                    string filename;
                    cout << "Nhap ten tep de luu du lieu: ";
                    cin >> filename;
                    saveToFile(list, filename);
                    break;
                }
            case 25:
                {
                    string filename;
                    cout << "Nhap ten tep de nap du lieu: ";
                    cin >> filename;
                    loadFromFile(list, filename);
                    break;
                }
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                break;
        }
    }
}


int main() {
    doubleList list;
    initialize(list);
    menu(list);
    return 0;
}

