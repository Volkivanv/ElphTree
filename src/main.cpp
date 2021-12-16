#include <iostream>
#include <string>
#include <ctime>
#include <vector>


class MiddleBranch{
    std::string name = "None";
    bool inhabited = false;
    int number = 0;
    class BigBranch* bigBranch = nullptr;
public:

    std::string getName(){
        return name;
    }
    bool getInhabited(){
        return inhabited;
    }
    int getNumber(){
        return number;
    }
    MiddleBranch(class BigBranch* inBigBranch, std::string inName, int inNumber): bigBranch(inBigBranch), name(inName), number(inNumber)
    {
        inhabited = (inName!="None");
    }
    int getNeighboursNumber();

 //  MiddleBranch();

};




class BigBranch
        {
    int count = 0;
    std::string name = "None";
    bool inhabited = false;
    int number = 0;
    std::vector<MiddleBranch*> middleBranches;
public:

    int getCount() const
    {
        return count;
    }
    int getNumber(){
        return number;
    }
    explicit BigBranch(int inCount, int inNumber): count(inCount), number(inNumber)
    {
      //  count = 2+rand()%2;
        middleBranches.resize(inCount);
        std::string inName;
        for(int i = 0; i < inCount; i++){

            std::cout<<"Input Elph Name on the middle Branch please!"<< std::endl;
            std::cin>>inName;
            middleBranches[i] = new MiddleBranch(this, inName, i);
        }
        std::cout<<"Input Elph Name on the Big branch please!"<< std::endl;
        std::cin >> inName;

        checkIn(inName);




    }
    MiddleBranch* getMiddleBranch(int index){
        if(index < 0) return nullptr;
        if(index>= this->count) return nullptr;
        return this->middleBranches[index];
    }
    void showElphs(){
        std::cout<<"Big branch #"<<this->getNumber()<<" on the root "<<getName()<<std::endl;
        for(int i = 0; i < count;i++){
            std::cout << "Big branch #" << this->getNumber() << " " << "Middle branch # " << middleBranches[i]->getNumber() << " "
                      << middleBranches[i]->getName() << std::endl;
        }
    }

    void checkIn(std::string inName){
        name = inName;
        inhabited = (inName!="None");
    }
    int getElphCount(){
        int sum = 0;
        if(this->inhabited) sum++;
        for(int i = 0; i < count; i++){
            if(middleBranches[i]->getInhabited()) sum++;
        }
        return sum;
    }
    int getNeighboursNumber(){
        return getElphCount()-1;
    }
    std::string getName(){
        return name;
    }
    bool getInhabited(){
        return inhabited;
    }


};

int MiddleBranch::getNeighboursNumber() {
    return this->bigBranch->getElphCount()-1;
}

class Tree{
    int count = 0;
    int number = 0;
    std::vector<BigBranch*> bigBranches;
public:
    int getCount(){
        return count;
    }
    int getNumber(){
        return number;
    }
    explicit Tree(int inCount, int inNumber):count(inCount), number(inNumber)
    {
        bigBranches.resize(inCount);
        for(int i = 0; i < count; i++){
            int inMiddleBranchCount = 2+rand()%2;
            bigBranches[i] = new BigBranch(inMiddleBranchCount, i);
        }
    }
    BigBranch* getBigBranch(int index){
        if(index < 0) return nullptr;
        if(index>= this->count) return nullptr;
        return this->bigBranches[index];
    }
    void showBranches(){
        for(int i = 0; i < count; i++){

            bigBranches[i]->showElphs();
        }
    }


};

class Forest{
    int count = 0;
    std::vector<Tree*> trees;
public:
    int getCount(){
        return count;
    }
    explicit Forest(int inCount):count(inCount)
    {
        trees.resize(inCount);

        for(int i = 0; i < count;i++){
            int inBranchCount = 3+rand()%3;
            trees[i] = new Tree(inBranchCount, i);
        }
    }
    void showTrees(){

        for(int i = 0; i < count;i++){
            std::cout<<"Tree number #"<<trees[i]->getNumber()<<std::endl;
            trees[i]->showBranches();
        }
    }

    int getNeighbourCount(std::string inName){

        for(int i = 0; i < count ; i++){
            for(int j = 0; j < trees[i]->getCount();j++){
                if((trees[i]->getBigBranch(j)->getName() == inName) &&
                   (trees[i]->getBigBranch(j)->getInhabited()))
                {
                    return trees[i]->getBigBranch(j)->getNeighboursNumber();
                }
                for(int k = 0; k < trees[i]->getBigBranch(j)->getCount(); k++){
                    if((trees[i]->getBigBranch(j)->getMiddleBranch(k)->getName() == inName) &&
                       (trees[i]->getBigBranch(j)->getMiddleBranch(k)->getInhabited()))
                    {
                        return trees[i]->getBigBranch(j)->getMiddleBranch(k)->getNeighboursNumber();
                    }
                }
            }
        }

        std::cout<<"This Elph is not found"<<std::endl;
        return -1;
    }
};

int main() {


    std::srand(std::time(nullptr));


    std::string inName;

    auto forest = new Forest(5);
   // forest->showTrees();
    std::cout<<"Input name of Elph of exit"<<std::endl;
    std::cin>>inName;
    while(inName!="exit") {
        std::cout << forest->getNeighbourCount(inName) << std::endl;
        std::cout<<"Input name of Elph of exit"<<std::endl;
        std::cin>>inName;
    }
    delete forest;



  return 0;
}
