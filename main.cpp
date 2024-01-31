#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef std::vector<std::string> StringArray;
std::vector<StringArray> command;
vector<float> costumer;
vector<float> cashToBarista;
vector<float> baristaQueuePriceSorted;
vector<float> newbaristaQueueSortedPrice;
vector<float> :: iterator it;



struct cashNode{
    struct cashNode* next;
    struct cashNode* prev;
    float arrivalTime;
    float orderTime;
    float brewTime;
    float price;
    float totalcashTime;
    float busyTimeCashier;
};

struct cashNode* head = NULL;
int a = 0;
int b = 0;
int count = 0;
int c = 0;
int d = 0;
int k = 0;
int l = 0;
int j = 0;
float y = 0;
float r = 0;
int maxsizeCashier = 0;
int maxsizeBarista = 0;

struct allCostumer{
    struct allCostumer* next;
    float CarrivalTime;
    float CorderTime;
    float CbrewTime;
    float Cprice;
    float CtotalcashTime;
    float CfinishTime;
    float coffeeready;
};
struct allCostumer* allcostumerHead = NULL;

struct baristaNode{
    struct baristaNode* next;
    float BarrivalTime;
    float BorderTime;
    float BbrewTime;
    float Bprice;
    float BtotalcashTime;
    float Bfinishtime;
    float busyTimeBarista;

};
struct baristaNode* baristanodeHead = NULL;


class Node{
public:
    float qarrivaltime;
    float qordertime;
    float qbrewtime;
    float qprice;
    float qsnextarrivel;
    float Ctotalcashtime;
    float finishTime;

    Node* next;

    Node(){
        next = NULL;
    };
};

class Queue{
public:

    Node* front;
    Node* rear;
    int size;
    Node* front_barista;
    Node* rear_barista;
    int size_barista;

    Queue(){
        front = NULL;
        rear = NULL;
        size = 0;
        front_barista = NULL;
        rear_barista = NULL;
        size_barista = 0;
    }
    double round(double var);
    Node* enqueu(float qatime, float qordert, float qbrewt, float qprice);
    Node* dequeu();
    Node* enqueue_barista(float arrival, float order, float brew, float price, float qtotalcashtime);
    Node* dequeue_barista();
    void firstModel();
    cashNode* cashierList();
    allCostumer* allCostumerList();
    baristaNode* baristaList();
    void firstmodelBarista(ofstream &outputFile);



};
double Queue::round(double var) {
    double value = (int) (var * 100 + .5);
    value = value / 100;

    return value;
}

allCostumer* Queue :: allCostumerList() {

    for (int i = 2; i < command.size(); ++i) {

        struct allCostumer* tempAllCostumer;
        allCostumer* newnode = new allCostumer();
        float carrivalTime = stof(command[i][0]);
        float corderTime = stof(command[i][1]);
        float cbrewTime = stof(command[i][2]);
        float cprice = stof(command[i][3]);
        float ctotalcashTime = stof(command[i][0]) + stof(command[i][1]);

        newnode->CarrivalTime = carrivalTime;
        newnode->CorderTime = corderTime;
        newnode->CbrewTime = cbrewTime;
        newnode->Cprice = cprice;
        newnode->CtotalcashTime = ctotalcashTime;
        newnode->coffeeready  =newnode->CtotalcashTime;


        if (allcostumerHead == NULL){
            allcostumerHead = newnode;
            newnode->next = NULL;
        } else{
            tempAllCostumer = allcostumerHead;
            while (tempAllCostumer->next != NULL){
                tempAllCostumer = tempAllCostumer->next;

            }
            newnode->next = NULL;
            tempAllCostumer->next = newnode;
        }
    }
    return allcostumerHead;
}


cashNode* Queue ::cashierList() {

    for (int i = 2; i < stoi(command[0][0]) + 2; ++i) {

        struct cashNode* temp;
        cashNode* new_node = new cashNode();

        float arrivaltime = stof(command[i][0]);
        float ordertime = stof(command[i][1]);
        float brewtime = stof(command[i][2]);
        float Price = stof(command[i][3]);
        float totalcashtime = stof(command[i][0]) + stof(command[i][1]);
        float busytime = stof(command[i][0]) + stof(command[i][1]);

        new_node->arrivalTime = arrivaltime;
        new_node->orderTime  = ordertime;
        new_node->brewTime = brewtime;
        new_node->price = Price;
        new_node->totalcashTime = totalcashtime;
        new_node->busyTimeCashier = busytime;

        struct allCostumer* tempcostumera = allcostumerHead;

        while (tempcostumera != NULL){
            if (tempcostumera->CarrivalTime == stof(command[i][0])){
                tempcostumera->coffeeready = tempcostumera->CorderTime + tempcostumera->CarrivalTime;

            }
            tempcostumera = tempcostumera->next;
        }

        if (head == NULL){
            head = new_node;
            new_node->next = NULL;
        }
        else{
            temp = head;

            while (temp->next != NULL){
                temp = temp->next;
            }

            new_node->next = NULL;
            temp->next = new_node;
        }

    }
    return head;
}

Node* Queue :: enqueu(float qatime, float qordert, float qbrewt, float qprice) {

    Node* new_node = new Node();

    new_node->qarrivaltime = qatime;
    new_node->qordertime = qordert;
    new_node->qbrewtime = qbrewt;
    new_node->qprice = qprice;

    if(rear == NULL){
        rear = new_node;
        front = new_node;

    }
    else{
        rear->next = new_node;
        rear = rear->next;
    }

    size++;

    if (size > maxsizeCashier){
        maxsizeCashier = size;
    }

    return front;
}

Node* Queue ::enqueue_barista(float arrival, float order, float brew, float price, float qtotalcashtime) {
    Node* newnodeBaristaQ = new Node();
    newnodeBaristaQ->qarrivaltime = arrival;
    newnodeBaristaQ->qordertime = order;
    newnodeBaristaQ->qbrewtime = brew;
    newnodeBaristaQ->qprice = price;
    newnodeBaristaQ->Ctotalcashtime = qtotalcashtime;


    if (rear_barista == NULL){
        rear_barista = newnodeBaristaQ;
        front_barista = newnodeBaristaQ;
    }
    else{
        rear_barista->next = newnodeBaristaQ;
        rear_barista = rear_barista->next;
    }

    newbaristaQueueSortedPrice.push_back(newnodeBaristaQ->qprice);

    int minipos;
    float tempa;

    for (int i = 0; i < newbaristaQueueSortedPrice.size(); ++i) {
        minipos = i;
        for (int j = i+1; j < newbaristaQueueSortedPrice.size(); ++j) {
            if (newbaristaQueueSortedPrice[j] > newbaristaQueueSortedPrice[minipos]){
                minipos = j;
            }
        }
        tempa = newbaristaQueueSortedPrice[minipos];
        newbaristaQueueSortedPrice[minipos] = newbaristaQueueSortedPrice[i];
        newbaristaQueueSortedPrice[i] = tempa;

    }


    size_barista++;
    if (size_barista > maxsizeBarista){
        maxsizeBarista = size_barista;
    }



    return front_barista;
}

Node* Queue ::dequeue_barista() {
    if(front_barista == NULL){
        return NULL;
    }
    Node* temp = front_barista;
    front_barista  =front_barista->next;

    if(front_barista == NULL){
        rear_barista = NULL;
    }
    delete(temp);
    size_barista--;

    return front_barista;

}

Node* Queue :: dequeu() {

    if (front == NULL){
        return NULL;
    }

    Node* temp = front;
    front = front->next;

    if (front == NULL){
        rear = NULL;
    }

    delete(temp);
    size--;

    return front;

}

int findSize(){
    struct cashNode* temp = head;

    while (temp != NULL){
        temp = temp->next;
        count++;
    }
    return count;
}


void Queue :: firstModel() {

    struct cashNode* tempB = head;

    for (int i = stoi(command[0][0]) + 2; i < command.size(); ++i) {
        costumer.push_back(stof(command[i][0]));

    }
    while (tempB != NULL){
        cashToBarista.push_back(tempB->totalcashTime);
        tempB  =tempB->next;
    }

    for (int i = 0; i < costumer.size(); ++i) {
        class Node* qnode = front;

        struct cashNode* temp = head;


        while (temp != NULL){

            if (temp->arrivalTime + temp->orderTime  > costumer.at(i)){
                a++;
                if (a == count){
                    enqueu(costumer.at(i), stof(command[stoi(command[0][0]) + 2 + i][1]),
                           stof(command[stoi(command[0][0]) + 2 + i][2]),
                           stof(command[stoi(command[0][0]) + 2 + i][3]));

                    it = costumer.begin() + i;
                }

            } else{

                if (size > 0){

                    struct allCostumer* tempcostumera = allcostumerHead;
                    while (tempcostumera != NULL){
                        if (tempcostumera->CarrivalTime == qnode->qarrivaltime){
                            tempcostumera->coffeeready = tempcostumera->CorderTime + temp->totalcashTime;

                        }
                        tempcostumera = tempcostumera->next;
                    }
                    temp->arrivalTime = qnode->qarrivaltime;
                    temp->orderTime = qnode->qordertime;

                    temp->totalcashTime += qnode->qordertime;
                    temp->busyTimeCashier += qnode->qordertime;

                    cashToBarista.push_back(temp->totalcashTime);

                    dequeu();

                } else{
                    b++;
                    if ( b == 1){
                        struct allCostumer* tempcostumerb = allcostumerHead;

                        while (tempcostumerb != NULL){
                            if (tempcostumerb->CarrivalTime == costumer.at(i)){

                                tempcostumerb->coffeeready = tempcostumerb->CarrivalTime + tempcostumerb->CorderTime;

                            }
                            tempcostumerb = tempcostumerb->next;
                        }
                        temp->busyTimeCashier += costumer.at(i) - temp->totalcashTime + stof(command[stoi(command[0][0]) + 2 + i][1]);
                        temp->arrivalTime = costumer.at(i);
                        temp->orderTime = stof(command[stoi(command[0][0]) + 2 + i][1]);
                        temp->totalcashTime = costumer.at(i) + stof(command[stoi(command[0][0]) + 2 + i][1]);

                        cashToBarista.push_back(temp->totalcashTime);

                        it = costumer.begin() + i;

                    }
                }
            }
            temp = temp->next;
        }
        a = 0;
        b = 0;

        struct cashNode* cashierNodenew = head;
        struct allCostumer* tempcostumernew = allcostumerHead;

        while (cashierNodenew != NULL){
            while (tempcostumernew != NULL){

                if (tempcostumernew->CarrivalTime == cashierNodenew->arrivalTime){
                    tempcostumernew->CtotalcashTime = cashierNodenew->totalcashTime;

                }tempcostumernew = tempcostumernew->next;
            }
            cashierNodenew = cashierNodenew->next;
        }

    }

}

baristaNode* Queue ::baristaList() {

    struct baristaNode* tempBaristaList;

    int minipos;
    float tempa;

    for (int i = 0; i < cashToBarista.size(); ++i) {
        minipos = i;
        for (int j = i+1; j < cashToBarista.size(); ++j) {
            if (cashToBarista[j] < cashToBarista[minipos]){
                minipos = j;
            }
        }
        tempa = cashToBarista[minipos];
        cashToBarista[minipos] = cashToBarista[i];
        cashToBarista[i] = tempa;
    }

    for (int i = 0; i < stoi(command[0][0])/3; ++i) {
        //cout << "a" << endl;
        baristaNode* newnode_ = new baristaNode();
        struct allCostumer* tempcost_ = allcostumerHead;
        struct allCostumer* tempcostumer = allcostumerHead;

        while (tempcostumer != NULL){

            if (cashToBarista.at(i) == tempcostumer->CtotalcashTime){

                float arriveltimeb = tempcostumer->CarrivalTime;
                float ordertimeb = tempcostumer->CorderTime;
                float brewtimeb = tempcostumer->CbrewTime;
                float priceb = tempcostumer->Cprice;
                float totalcashtimeb = tempcostumer->CtotalcashTime;
                float busyTimeBarista = tempcostumer->CbrewTime;
                float finishTime = tempcostumer->CtotalcashTime + tempcostumer->CbrewTime;

                tempcostumer->CfinishTime = tempcostumer->CtotalcashTime + tempcostumer->CbrewTime;

                newnode_->BarrivalTime = arriveltimeb;
                newnode_->BorderTime = ordertimeb;
                newnode_->BbrewTime = brewtimeb;
                newnode_->Bprice = priceb;
                newnode_->BtotalcashTime = totalcashtimeb;
                newnode_->Bfinishtime = finishTime;
                newnode_->busyTimeBarista = busyTimeBarista;


                if (baristanodeHead == NULL){
                    baristanodeHead = newnode_;
                    newnode_->next = NULL;
                }
                else{

                    tempBaristaList = baristanodeHead;

                    while (tempBaristaList->next != NULL){
                        tempBaristaList = tempBaristaList->next;
                    }
                    newnode_->next = NULL;
                    tempBaristaList->next = newnode_;

                }
            }
            tempcostumer = tempcostumer->next;
        }

    }
    for (int i = stoi(command[0][0])/3; i < cashToBarista.size(); ++i) {

        struct allCostumer* tempcostumer_ = allcostumerHead;

        while (tempcostumer_ != NULL){
            if (cashToBarista.at(i) == tempcostumer_->CtotalcashTime){
                baristaQueuePriceSorted.push_back(cashToBarista.at(i)); //bunu kullan
            }
            tempcostumer_ = tempcostumer_->next;
        }
    }


    return baristanodeHead;
}

void Queue ::firstmodelBarista(ofstream &outputFile) {


    struct allCostumer* allCostumersTemp = allcostumerHead;

    for (int i = 0; i < baristaQueuePriceSorted.size(); ++i) {

    class Node* baristaQueuetemp = front_barista;
    struct baristaNode* baristaNodesTemp = baristanodeHead;
    struct allCostumer* tempinsideallcostumer = allcostumerHead;
    struct allCostumer* tempinsideallcostumer2 = allcostumerHead;
    struct allCostumer* tempinsideallcostumer3 = allcostumerHead;
    struct allCostumer* tempinsideallcostumer4 = allcostumerHead;
    struct allCostumer* tempinsideallcostumer5 = allcostumerHead;

    while (baristaNodesTemp != NULL){
        if (baristaNodesTemp->Bfinishtime > baristaQueuePriceSorted.at(i)){
            j++;
            k++;
            if (k == count/3){
                while (tempinsideallcostumer != NULL){
                    if (baristaQueuePriceSorted.at(i) == tempinsideallcostumer->CtotalcashTime){

                        enqueue_barista(tempinsideallcostumer->CarrivalTime , tempinsideallcostumer->CorderTime , tempinsideallcostumer->CbrewTime, tempinsideallcostumer->Cprice , tempinsideallcostumer->CtotalcashTime);
                    }
                    tempinsideallcostumer = tempinsideallcostumer->next;
                }
            }
            if (l + j == count/3 && j > 0 && l > 0){
                while (tempinsideallcostumer3 != NULL){
                    if (baristaQueuePriceSorted.at(i) == tempinsideallcostumer3->CtotalcashTime){
                        enqueue_barista(tempinsideallcostumer3->CarrivalTime , tempinsideallcostumer3->CorderTime ,
                                        tempinsideallcostumer3->CbrewTime, tempinsideallcostumer3->Cprice ,
                                        tempinsideallcostumer3->CtotalcashTime);
                    }
                    tempinsideallcostumer3 = tempinsideallcostumer3->next;
                }
            }
        } else{

            if (size_barista > 0){
                c++;
                l++;



                if (c == count/3){
                    while (tempinsideallcostumer2 != NULL){
                        if (baristaQueuePriceSorted.at(i) == tempinsideallcostumer2->CtotalcashTime){
                            enqueue_barista(tempinsideallcostumer2->CarrivalTime , tempinsideallcostumer2->CorderTime ,
                                            tempinsideallcostumer2->CbrewTime, tempinsideallcostumer2->Cprice ,
                                            tempinsideallcostumer2->CtotalcashTime);
                        }
                        tempinsideallcostumer2 = tempinsideallcostumer2->next;
                    }
                }
                if (l + j == count/3 && j > 0 && l > 0){
                    while (tempinsideallcostumer4 != NULL){
                        if (baristaQueuePriceSorted.at(i) == tempinsideallcostumer4->CtotalcashTime){
                            enqueue_barista(tempinsideallcostumer4->CarrivalTime , tempinsideallcostumer4->CorderTime ,
                                            tempinsideallcostumer4->CbrewTime, tempinsideallcostumer4->Cprice ,
                                            tempinsideallcostumer4->CtotalcashTime);
                        }
                        tempinsideallcostumer4 = tempinsideallcostumer4->next;
                    }
                }

                while (tempinsideallcostumer5 != NULL){           //burayı düzelt
                    if (newbaristaQueueSortedPrice.at(0) == tempinsideallcostumer5->Cprice){

                        baristaNodesTemp->busyTimeBarista += tempinsideallcostumer5->CbrewTime;
                        tempinsideallcostumer5->coffeeready = baristaNodesTemp->Bfinishtime + tempinsideallcostumer5->CbrewTime;
                        baristaNodesTemp->Bfinishtime += tempinsideallcostumer5->CbrewTime;
                        baristaNodesTemp->BarrivalTime = tempinsideallcostumer5->CarrivalTime;
                        baristaNodesTemp->BorderTime = tempinsideallcostumer5->CorderTime;
                        baristaNodesTemp->BbrewTime = tempinsideallcostumer5->CbrewTime;
                        baristaNodesTemp->Bprice = newbaristaQueueSortedPrice.at(0);
                        baristaNodesTemp->BtotalcashTime = tempinsideallcostumer5->CtotalcashTime;



                    }
                     tempinsideallcostumer5  = tempinsideallcostumer5->next;
                }

                dequeue_barista();
                it = newbaristaQueueSortedPrice.begin();
                newbaristaQueueSortedPrice.erase(it);

            } else{
                struct allCostumer* tempinsideallcostumerSizeBaristaPositive = allcostumerHead;
                d++;
                if (d == 1){
                    while (tempinsideallcostumerSizeBaristaPositive != NULL){
                        if (baristaQueuePriceSorted.at(i) == tempinsideallcostumerSizeBaristaPositive->CtotalcashTime){
                            baristaNodesTemp->busyTimeBarista = baristaQueuePriceSorted.at(i) - baristaNodesTemp->Bfinishtime + tempinsideallcostumerSizeBaristaPositive->CbrewTime;
                            tempinsideallcostumerSizeBaristaPositive->coffeeready = baristaQueuePriceSorted.at(i) - baristaNodesTemp->Bfinishtime + tempinsideallcostumerSizeBaristaPositive->CbrewTime;
                            baristaNodesTemp->Bfinishtime += baristaNodesTemp->Bfinishtime - tempinsideallcostumerSizeBaristaPositive->CtotalcashTime + tempinsideallcostumerSizeBaristaPositive->CbrewTime;
                            baristaNodesTemp->BarrivalTime = tempinsideallcostumerSizeBaristaPositive->CarrivalTime;
                            baristaNodesTemp->BorderTime = tempinsideallcostumerSizeBaristaPositive->CorderTime;
                            baristaNodesTemp->BbrewTime = tempinsideallcostumerSizeBaristaPositive->CbrewTime;
                            baristaNodesTemp->Bprice = tempinsideallcostumerSizeBaristaPositive->Cprice;


                        }
                        tempinsideallcostumerSizeBaristaPositive = tempinsideallcostumerSizeBaristaPositive->next;
                    }
                }
            }
        }

        baristaNodesTemp = baristaNodesTemp->next;

    }
        c = 0;
        d = 0;
        k = 0;
        l = 0;
        j = 0;
}

struct baristaNode* baristaNodesTemp_ = baristanodeHead;
struct baristaNode* baristaNodesTemp_next = baristaNodesTemp_->next;


if (size_barista > 0){

        for (int i = 0; i < newbaristaQueueSortedPrice.size(); ++i) {
            struct allCostumer* tempinsideallcostumer7 = allcostumerHead;
            struct allCostumer* tempinsideallcostumer6 = allcostumerHead;

            y = baristaNodesTemp_->Bfinishtime;
            r = baristaNodesTemp_next->Bfinishtime;


            if (baristanodeHead->Bfinishtime < baristanodeHead->next->Bfinishtime){
                while (tempinsideallcostumer7 != NULL){
                    if (newbaristaQueueSortedPrice.at(i) == tempinsideallcostumer7->Cprice){
                        baristanodeHead->busyTimeBarista += tempinsideallcostumer7->CbrewTime;
                        tempinsideallcostumer7->coffeeready += baristanodeHead->Bfinishtime + tempinsideallcostumer7->CbrewTime;
                        baristanodeHead->Bfinishtime += tempinsideallcostumer7->CbrewTime;
                        baristanodeHead->BarrivalTime = tempinsideallcostumer7->CarrivalTime;
                        baristanodeHead->BorderTime = tempinsideallcostumer7->CorderTime;
                        baristanodeHead->BbrewTime = tempinsideallcostumer7->CbrewTime;
                        baristanodeHead->Bprice = tempinsideallcostumer7->Cprice;


                    }
                    tempinsideallcostumer7 = tempinsideallcostumer7->next;
                }
            } else{
                while (tempinsideallcostumer6 != NULL){
                    if (newbaristaQueueSortedPrice.at(i) == tempinsideallcostumer6->Cprice){
                        baristanodeHead->next->busyTimeBarista += tempinsideallcostumer6->CbrewTime;
                        baristanodeHead->next->Bfinishtime += tempinsideallcostumer6->CbrewTime;
                        tempinsideallcostumer6->coffeeready += baristanodeHead->Bfinishtime + tempinsideallcostumer6->CbrewTime;
                        baristanodeHead->next->BarrivalTime = tempinsideallcostumer6->CarrivalTime;
                        baristanodeHead->next->BorderTime = tempinsideallcostumer6->CorderTime;
                        baristanodeHead->next->BbrewTime = tempinsideallcostumer6->CbrewTime;
                        baristanodeHead->next->Bprice = tempinsideallcostumer6->Cprice;

                    }

                    tempinsideallcostumer6 = tempinsideallcostumer6->next;
                }
            }

        }
    }




struct cashNode* tempa = head;
struct baristaNode* baristaNodesTemp_i = baristanodeHead;
struct allCostumer* tempinsideallcostumerprinting = allcostumerHead;

outputFile << baristanodeHead->next->Bfinishtime << endl;
outputFile << maxsizeCashier << endl;
outputFile << maxsizeBarista << endl;

while (tempa != NULL){



    outputFile  << round(tempa->busyTimeCashier/baristanodeHead->next->Bfinishtime) << endl;
    tempa = tempa->next;
}
while (baristaNodesTemp_i != NULL){

    outputFile  <<round(baristaNodesTemp_i->busyTimeBarista/baristanodeHead->next->Bfinishtime ) << endl;
    baristaNodesTemp_i = baristaNodesTemp_i->next;
}
while (tempinsideallcostumerprinting != NULL){

    outputFile  << round(tempinsideallcostumerprinting->coffeeready - tempinsideallcostumerprinting->CarrivalTime)    << endl;
    tempinsideallcostumerprinting = tempinsideallcostumerprinting->next;
}
}


int main(int argc, char *argv[]) {

    std::ifstream file;
    file.open(argv[1]);

    std::string line, tempStr;

    while (std::getline(file, line))
    {
        command.push_back(StringArray());
        // now parse the line
        std::istringstream strm(line);
        while (strm >> tempStr)
            // add string to the last added vector
            command.back().push_back(tempStr);
    }

    file.close();

    ofstream outputFile;

    outputFile.open(argv[2]);



    float qatime;
    float qordert;
    float qbrewt;
    float qprice;
    Queue queue;


    //commandVector();
    queue.allCostumerList();
    queue.cashierList();
    findSize();
    queue.dequeu();
    queue.dequeue_barista();
    queue.firstModel();
    queue.baristaList();
    queue.firstmodelBarista(outputFile);

    outputFile.close();

    return 0;
}
