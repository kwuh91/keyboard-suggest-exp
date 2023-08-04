#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

struct Node {
    std::string word;
    int count;
    Node *next;
};

void addend(Node **head, std::string new_word) {
    Node *new_node = new Node;
    Node *last = *head;
    new_node->word = new_word;
    new_node->count = 1;
    new_node->next = nullptr;
    if (*head == nullptr) {
        *head = new_node;
        return;
    }
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = new_node;
}

void struct_unique_word_counter(Node **head, std::string new_word) {
    Node *temp_head = *head;
    if (*head == nullptr) {
        addend(head, new_word);
        return;
    }
    if ((*head)->word == new_word) {
        ++((*head)->count);
        return;
    }
    while ((temp_head != nullptr) && (temp_head->word != new_word)) {
        temp_head = temp_head->next;
    }
    if (temp_head != nullptr) {
        ++(temp_head->count);
    } else {
        addend(head, new_word);
    }
}

void swap(struct Node *a, struct Node *b) {
    std::string temp = a->word;
    int temp2 = a->count;
    a->word = b->word;
    a->count = b->count;
    b->word = temp;
    b->count = temp2;
}

void bubbleSort_num(struct Node *start) {
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = nullptr;

    if (start == nullptr)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->count < ptr1->next->count) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

std::vector<std::string>
first_specific_ten_popular_words(Node *head, std::vector<std::string> vec, std::string condition) {
    size_t length = condition.length();
    while (vec.size() < 10 && head != nullptr) {
        bool flag = true;
        for (size_t i = 0; i < length; ++i) {
            if (!(head->word[i] == condition[i] || head->word[i] == toupper(condition[i]) ||
                  head->word[i] == tolower(condition[i]))) {
                flag = false;
                break;
            }
        }
        if (flag) {
            vec.push_back(head->word);
        }
        head = head->next;
    }
    return vec;
}

std::string conversion_to_SMALL(std::string str) {
    for (size_t i = 0; i < str.length(); ++i) {
        str[i] = tolower(str[i]);
    }
    return str;
}

void destruct(struct Node **head) {
    struct Node *temp = *head;
    struct Node *next;
    while (temp != nullptr) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    *head = nullptr;
}

bool check(Node **head, std::string str) {
    while (str[str.length() - 1] == '.' || str[str.length() - 1] == ',' ||
           str[str.length() - 1] == '!' || str[str.length() - 1] == '?' ||
           str[str.length() - 1] == '(' || str[str.length() - 1] == ')' ||
           str[str.length() - 1] == ']' || str[str.length() - 1] == '[' ||
           str[str.length() - 1] == ';' || str[str.length() - 1] == ':' ||
           str[str.length() - 1] == '{' || str[str.length() - 1] == '}' ||
           str[str.length() - 1] == '>' || str[str.length() - 1] == '<' ||
           str[str.length() - 1] == '/' || str[str.length() - 1] == '-' ||
           str[str.length() - 1] == '_' || str[str.length() - 1] == '*') {
        str.pop_back();
    }
    while (str[0] == '.' || str[0] == ',' ||
           str[0] == '!' || str[0] == '?' ||
           str[0] == '(' || str[0] == ')' ||
           str[0] == ']' || str[0] == '[' ||
           str[0] == ';' || str[0] == ':' ||
           str[0] == '{' || str[0] == '}' ||
           str[0] == '>' || str[0] == '<' ||
           str[0] == '/' || str[0] == '-' ||
           str[0] == '_' || str[0] == '*') {
        str.erase(0, 1);
    }
    if (str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") > str.length() &&
        str.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") < str.length() &&
        str.length() > 1) {
        str = conversion_to_SMALL(str);
        struct_unique_word_counter(head, str);
        return true;
    } else {
        return false;
    }
}

void struct_formation_for_continuation(Node **head, std::ifstream &myfile, int accuracy) {
    myfile.open("wiki.xml");
    //myfile.open("exp.txt");
    std::string myline;
    if (myfile.is_open()) {
        int count = 0;
        while (count < accuracy && myfile) {
            std::getline(myfile, myline);
            //std::cout << myline << '\n';
            //words_starting_with_leter('h', myline);
            for (size_t i = 0; i < myline.length(); ++i) {
                std::string str;
                if (i == 0 || myline[i - 1] == ' ') {
                    while (myline[i] != ' ' && i < myline.length()) {
                        str += myline[i];
                        ++i;
                    }
                    //std::cout << str << std::endl;
                    //check(head,str);
                    if (check(head, str)) {
                        ++count;
                    }
                    //std::cout << "Word added!\n";
                    str.clear();
                }
            }
        }
    } else {
        std::cout << "Couldn't open file\n";
    }
    myfile.close();
}

void struct_formation_for_words_after(Node **head, std::ifstream &myfile, int accuracy, std::string word) {
    myfile.open("wiki.xml");
    std::string myline;
    if (myfile.is_open()) {
        int count = 0;
        while (count < accuracy && myfile) {
            std::getline(myfile, myline);
            for (size_t i = 0; i < myline.length(); ++i) {
                if ((myline[i] == word[0] && myline[i - 1] == ' ') || (myline[i] == word[0] && i == 0)) {
                    bool flag = true;
                    for (size_t j = 0; j < word.length(); ++j) {
                        if (myline[i] != word[j]) {
                            flag = false;
                            break;
                        }
                        ++i;
                    }
                    if (flag) {
                        std::string str;
                        ++i;
                        while (myline[i] != ' ' && i < myline.length()) {
                            str += myline[i];
                            ++i;
                        }
                        //check(head,str);
                        if (check(head, str)) {
                            ++count;
                        }
                        //std::cout << "Word added!\n";
                        str.clear();
                    }
                }
            }
        }
    } else {
        std::cout << "Couldn't open file\n";
    }
    myfile.close();
}

std::vector<std::string> first_ten_words_after(Node *head, std::vector<std::string> vec) {
    int count = 0;
    while (head != nullptr && count < 10) {
        vec.push_back(head->word);
        head = head->next;
        ++count;
    }
    return vec;
}

int main() {
    std::vector<std::string> suggestion;
    Node *head = nullptr;
    std::ifstream myfile;
    std::cout << "Enter accuracy(how many words do you want to check in the file:)\n";
    int accuracy;
    std::cin >> accuracy;
    //display(head);
    while (true) {
        int choice;
        std::cout
                << "Enter:\n -1 to stop\n 1 to check for popular continuations\n 2 to check for popular words after\n";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::cout << "Processing...\n";
                struct_formation_for_continuation(&head, myfile, accuracy);
                bubbleSort_num(head);
                std::cout << "Enter your word:\n";
                std::string your_str;
                std::cin >> your_str;
                suggestion = first_specific_ten_popular_words(head, suggestion, your_str);
                for (auto i: suggestion) {
                    std::cout << i << " ";
                }
                std::cout << std::endl;
                suggestion.clear();
                destruct(&head);
                break;
            }
            case 2: {
                std::string myword;
                std::cout << "Enter your word:\n";
                std::cin >> myword;
                std::cout << "Processing...\n";
                struct_formation_for_words_after(&head, myfile, accuracy, myword);
                bubbleSort_num(head);
                //display(head);
                suggestion = first_ten_words_after(head, suggestion);
                for (auto i: suggestion) {
                    std::cout << i << " ";
                }
                std::cout << std::endl;
                suggestion.clear();
                destruct(&head);
                break;
            }
            case -1:
                return 0;
            default:
                std::cout << "Invalid input\n";
                break;
        }
    }
}
