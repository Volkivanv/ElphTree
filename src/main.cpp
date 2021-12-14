#include <iostream>
#include <string>
#include <ctime>


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
    MiddleBranch** middleBranchs = nullptr;
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
        middleBranchs = new MiddleBranch*[inCount];
        std::string inName;
        for(int i = 0; i < inCount; i++){

            std::cout<<"Input Elph Name on the middle Branch please!"<< std::endl;
            std::cin>>inName;
            middleBranchs[i] = new MiddleBranch(this, inName,i);
        }
        std::cout<<"Input Elph Name on the Big branch please!"<< std::endl;
        std::cin >> inName;

        checkIn(inName);




    }
    MiddleBranch* getMiddleBranchAtIndex(int index){
        if(this == nullptr) return nullptr;
        if(index < 0) return nullptr;
        if(index>= this->count) return nullptr;
        return this->middleBranchs[index];
    }
    void showElphs(){
        std::cout<<"Big branch #"<<this->getNumber()<<" on the root "<<getName()<<std::endl;
        for(int i = 0; i < count;i++){
            std::cout<<"Big branch #"<<this->getNumber()<<" "<<"Middle branch # "<< middleBranchs[i]->getNumber()<<" "
            <<middleBranchs[i]->getName()<<std::endl;
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
            if(middleBranchs[i]->getInhabited()) sum++;
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
    BigBranch** bigBranch = nullptr;
public:
    int getCount(){
        return count;
    }
    int getNumber(){
        return number;
    }
    explicit Tree(int inCount, int inNumber):count(inCount), number(inNumber)
    {
        bigBranch = new BigBranch*[inCount];
        for(int i = 0; i < count; i++){
            int inMiddleBranchCount = 2+rand()%2;
            bigBranch[i] = new BigBranch(inMiddleBranchCount,i);
        }
    }
    BigBranch* getBigBranchAtIndex(int index){
        if(this == nullptr) return nullptr;
        if(index < 0) return nullptr;
        if(index>= this->count) return nullptr;
        return this->bigBranch[index];
    }
    void showBranchs(){
        for(int i = 0; i < count; i++){

            bigBranch[i]->showElphs();
        }
    }


};

class Forest{
    int count = 0;
    Tree** trees = nullptr;
public:
    int getCount(){
        return count;
    }
    explicit Forest(int inCount):count(inCount)
    {
        trees = new Tree*[count];

        for(int i = 0; i < count;i++){
            int inBranchCount = 3+rand()%3;
            trees[i] = new Tree(inBranchCount, i);
        }
    }
    void showTrees(){

        for(int i = 0; i < count;i++){
            std::cout<<"Tree number #"<<trees[i]->getNumber()<<std::endl;
            trees[i]->showBranchs();
        }
    }

    int getNumberNeighboursFromName(std::string inName){
        bool found = false;
        for(int i = 0; i < count ; i++){
            for(int j = 0; j < trees[i]->getCount();j++){
                if((trees[i]->getBigBranchAtIndex(j)->getName() == inName)&&
                (trees[i]->getBigBranchAtIndex(j)->getInhabited())) {
                    found = true;
                    return trees[i]->getBigBranchAtIndex(j)->getNeighboursNumber();

                }
                for(int k = 0; k < trees[i]->getBigBranchAtIndex(j)->getCount();k++){
                    if((trees[i]->getBigBranchAtIndex(j)->getMiddleBranchAtIndex(k)->getName() == inName)&&
                    (trees[i]->getBigBranchAtIndex(j)->getMiddleBranchAtIndex(k)->getInhabited())){
                        found = true;
                        if(trees[i]->getBigBranchAtIndex(j)->getInhabited()) {
                            return trees[i]->getBigBranchAtIndex(j)->getMiddleBranchAtIndex(k)->getNeighboursNumber();
                        } else{
                            return trees[i]->getBigBranchAtIndex(j)->getMiddleBranchAtIndex(k)->getNeighboursNumber();
                        }

                    }
                }
            }
        }
        if(!found){
            std::cout<<"This Elph is not found"<<std::endl;
            return -1;
        }
    }
};

int main() {

  //  auto home1 = new Home("Bilboo");
    //home1->checkIn("Bilboo");
  //  std::cout << home1->getName() << std::boolalpha << home1->getInhabited()<<std::endl;
    std::srand(std::time(nullptr));
   // int count = 3+rand()%3;
    //std::cout<<count<<std::endl;

    std::string inName;

    auto forest = new Forest(2);
    forest->showTrees();
    std::cout<<"Input name of Elph of exit"<<std::endl;
    std::cin>>inName;
    while(inName!="exit") {
        std::cout << forest->getNumberNeighboursFromName(inName) << std::endl;
        std::cout<<"Input name of Elph of exit"<<std::endl;
        std::cin>>inName;
    }



  return 0;
}
