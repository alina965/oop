#pragma once

class Cell {
public:
    Cell(bool alive = false);
    virtual ~Cell() = default;
    virtual bool IsAlive() const = 0;
protected:
    bool alive_;
};
