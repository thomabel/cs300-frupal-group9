#include "Hero.h"

class TileType
{
public:
    virtual ~TileType() = 0;

    virtual bool canEnter(const Hero& theHero) const;
    virtual int energyCost() const;
    virtual int color() const = 0;
};

class Meadow : public TileType
{
    int color() const override;
};

class Wall : plublic TileType
{
    bool canEnter(const Hero& theHero) const override;
    int color() const override;
};

class Swamp : public TileType
{
    int energyCost() const override;
    int color() const override;
};

class Water : public TileType
{
    bool canEnter(const Hero& theHero) const override;
    int energyCost() const override;
    int color() const override;
}