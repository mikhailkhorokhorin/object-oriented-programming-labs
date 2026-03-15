#pragma once

class Bear;
class Rogue;
class Werewolf;
class NPC;

class Visitor {
   public:
    virtual ~Visitor() = default;

    virtual void visit(Bear& attacker, NPC& defender) = 0;
    virtual void visit(Rogue& attacker, NPC& defender) = 0;
    virtual void visit(Werewolf& attacker, NPC& defender) = 0;
};
