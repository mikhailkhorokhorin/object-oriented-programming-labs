#pragma once

class Bear;
class Rogue;
class Werewolf;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visit(Bear& npc) = 0;
    virtual void visit(Rogue& npc) = 0;
    virtual void visit(Werewolf& npc) = 0;
};
