//
//  main.cpp
//  MonsterArena
//
//  Created by Apple on 2020/01/05.
//  Copyright © 2020 Apple. All rights reserved.
//

#include <iostream>

enum Element
{
    fire,
    wind,
    water,
    earth
};

class Monster
{
public:
    bool isDead;
    Monster()
    {
        
    }
    
    Monster(std::string name, int hp,
            int attack, int defence, Element element)
    {
        mName = name;
        mHP = hp;
        mAttack = attack;
        mDefence = defence;
        mElement = element;
    }
    
    void PrintInfo()
    {
        std::cout << "이름 : " << mName << " hp : "<< mHP<< " 공격력 : " << mAttack << " 방어력 : " << mDefence << std::endl;
    }
    
    void AttackSelf(int damage)
    {
        mHP = mHP - damage;
    }

    void DoDamage(Monster& otherMonster)
    {
        int damage = CalcDamage(otherMonster);
        otherMonster.mHP = otherMonster.mHP - damage;
        std::cout << mName <<" 이" << otherMonster.mName << " 에게 " << damage << "피해를 입혔습니다." << std::endl;
        
        if(otherMonster.mHP <= 0)
        {
            isDead = 1;
        }
        
    }
    

    
private:
    std::string mName; // 멤버 변수 네이밍
    int mHP;
    int mAttack;
    int mDefence;
    Element mElement;
    
    int CalcDamage(Monster otherMonster)
    {
        std::cout << mName << std::endl;
        int attack = mAttack;
        int defence = otherMonster.mDefence;
        int damage = attack - defence;
        if(damage < 1)
        {
            damage = 1;
        }
        // 데미지 기본 계산d
        // 상성에는 세 가지 상태가 있음. 상성(1.5), 무상성(1), 역상성(0.5).
        // 2차원 배열 사용
        
        float relArray[4][4] =
        {{1,1.5,0.5,0.5},{0.5, 1, 1.5, 1.5},{1.5, 0.5, 1, 1},{1.5, 0.5, 1, 1}};
        //불 -> 바람 -> 물 -> 땅 순서
        float relations = relArray[mElement][otherMonster.mElement];
        
        damage = relations * damage;
        
        return damage;
    }
   
};

class Arena
{
    private:
    int arenaIndex = 0;
    Monster arenaMonster[100]={};
    
public :
    Arena()
    {
        std::cout << "아레나가 생성되었습니다" << std::endl;
    }

    void addToArena(Monster monsterNow)
    {
    //arena에 몬스터를 추가하는 함수
        
        arenaMonster[arenaIndex] = monsterNow;
        std::cout << arenaMonster[arenaIndex] << std::endl;
        arenaIndex++;
        
        
    }
    
    void GoToRound()
    {
        //몬스터를 순서대로 때림. 3명이면 1->2->3->1...
        //자기 뒤에 번호가 없으면 1번을 때림? 자기가 마지막이면...
        //생명력이 0인 몬스터는 아레나에서 사라짐
        int lastNumber;
        lastNumber = arenaIndex;
        
        for (int i = 0; i <= lastNumber; i++) {
            arenaMonster[i].DoDamage(arenaMonster[i+1]);
            
            if(i == lastNumber)
            {
                arenaMonster[lastNumber].DoDamage(arenaMonster[1]);
            }
            
            
            if(arenaMonster[i+1].isDead == 1)
            {
                Monster temp = arenaMonster[lastNumber];
                arenaMonster[lastNumber] = arenaMonster[i+1];
                arenaMonster[i+1] = temp;
                --lastNumber;
            }
        }
        
        
        
    }
    void SizeofArena()
    {
        // 현재 아레나에 있는 몬스터의 수를 가져오는 함수
        // sizeof 쓰고 배열 크기 가져오면 될 것 같은데...
        int size = sizeof(arenaMonster);
        std::cout << size << std::endl;
        
    }
    

};

int main(int argc, const char * argv[])
{
    Monster mon1("고블린", 10, 30, 10, earth);
    Monster mon2("오크", 20, 5, 20, wind);
    Monster mon3("슬라임", 5, 40, 40, fire);
    mon1.PrintInfo();
    mon2.PrintInfo();
    mon3.PrintInfo();
    Arena arena;
    arena.addToArena(mon1);
    
    
    
    

}
