#include <iostream>
#include <vector>

using namespace std;

enum condition {
    bad, satisfactorily, good
};
enum health {
    dead, alive, healthy
};

class Human {
    string name;
    health humanHealth;
    unsigned int age;
    vector <string*> myDrug;
public:
    Human(string _name, health _health) {
        name = _name;
        humanHealth = _health;
    };

    void setHumanHealth(health _humanHealth) {
        humanHealth = _humanHealth;
    }

    const string &getName() const {
        return name;
    }

    health getHumanHealth() const {
        return humanHealth;
    }

    unsigned int getAge() const{
        return age;
    }
    void setAge(unsigned int _age) {
        age = _age;
    }

    vector <string*> getHisDrugs(){
        return myDrug;
    }

    void takeHimNewDrug(string *_drug){
        myDrug.push_back(_drug);
    }
};

class Hospital {
    string name;
    vector <Human*> clients;
public:
    Hospital(string _name){
        name = _name;
    }
    void registrate(Human *human){
        clients.push_back(human);
    }
    const string getHospitalName() const {
        return name;
    }
    virtual condition makeAnalyzes(Human *human){};
    virtual bool getTreatment(Human *human){};
};

class Surgery : public Hospital {
    string hospitalName;
    bool getTreatment(Human *human) {
        if ((rand() % 20) > 10) {
            human->setHumanHealth(dead);
            cout << "We are sorry, you are dead now." << endl;
            return false;
        }
        human->setHumanHealth(healthy);
        cout << "Congrats, you are lucky and healthy" << endl;
        return true;
    }
public:
    Surgery(string _name) : Hospital(_name){
        hospitalName = _name;
    }

    const string getHospitalName() const {
        return hospitalName;
    }

    condition makeAnalyzes(Human *human) {
        switch (human->getHumanHealth()) {
            case dead:
                return bad;
            case alive:
                getTreatment(human);
                return (human->getHumanHealth() == dead) ? bad : good;
            case healthy:
                return good;
        }
    }
};

class Dentistry : public Hospital {
    string hospitalName;
    bool getTreatment(Human *human) {
        human->setHumanHealth(alive);
        return true;
    }
public:
    Dentistry(string _name) : Hospital(_name){
        hospitalName = _name;
    }

    const string getHospitalName() const {
        return hospitalName;
    }

    condition makeAnalyzes(Human *human) {
        if (human->getAge() < 16) return good;
        if (human->getAge() < 40){
            getTreatment(human);
            return satisfactorily;
        }
        if (human->getAge() < 100) return bad;
    }
};

class Therapy : public Hospital {
    string hospitalName;
    string drug;

    bool getTreatment(Human *human) {
        if (human->getAge() > 60) return false;
        string newDrugForHisHealth;
        human->takeHimNewDrug(&newDrugForHisHealth);
        return true;
    }
public:
    Therapy(string _name) : Hospital(_name){
            hospitalName = _name;
    }

    const string getHospitalName() const {
        return hospitalName;
    }

    condition makeAnalyzes(Human *human) {
        switch (human->getHumanHealth()) {
            case dead:
                return bad;
            case alive:
                return (getTreatment(human)) ? good : bad;
            case healthy:
                return good;
        }
    }
};

class Cardiology : public Hospital {
    string hospitalName;
    bool getTreatment(Human *human) {
        if (human->getAge() > 60) return false;
        string newDrugForHisHealth;
        human->takeHimNewDrug(&newDrugForHisHealth);
        human->setAge(human->getAge() + 10);
        return true;
    }
public:
    Cardiology(string _name) : Hospital(_name){
            hospitalName = _name;
    }

    const string getHospitalName() const {
        return hospitalName;
    }

    condition makeAnalyzes(Human *human) {
        switch (human->getHumanHealth()) {
            case dead:
                return bad;
            case alive:
                getTreatment(human);
                return (human->getAge() > 80) ? bad : good;
            case healthy:
                return good;
        }
    }
};

int main() {
    Hospital stJohn("st John Hospital");
    Human nadia("Nadia", alive);
    nadia.setAge(70);
    stJohn.registrate(&nadia);
    Surgery surgery(stJohn.getHospitalName());
    surgery.makeAnalyzes(&nadia);
    return 0;
}
