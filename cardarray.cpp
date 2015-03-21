#include "cardarray.h"
#include "universal.h"

CardArray::CardArray(QString arr) :
    _arr(arr), _cardCnt(arr.length()),
    _maxn(0), type(CardArray::Invalid)
{
    refresh();
}

CardArray::~CardArray()
{

}

void CardArray::clear()
{
    _arr = "";
    _cardCnt = 0;
    _maxn = 0;
    type = CardArray::Empty;
    FOR_TO(0, 19) count[i]=0;
}

void CardArray::addCard(char cd)
{
    _arr.append(cd);
    _cardCnt++;
    refresh();
}

void CardArray::copyArrayTo(CardArray obj)
{
    obj.clear();
    obj._arr = _arr; //=.=
    obj.refresh();
}

bool CardArray::isSameAs(CardArray obj)
{
    if (_arr==obj._arr) return true;
    else return false;
}

bool CardArray::isBiggerThan(CardArray obj) const
{
    if (obj.getType()==CardArray::Invalid)
        qDebug("CardArray is compared to a invalid one.");
    switch (type) {
    case CardArray::Empty:
    case CardArray::Invalid:
        return false;
        break;
    case CardArray::Bomb:
        if (obj.getType()==CardArray::Bomb)
        {
            if (_cardCnt>obj.getN()
                    || (_cardCnt==obj.getN()
                        && _maxn>obj.getMaxN()))
                    return true;
            else return false;
        } else {
            return true;
        }
        break;
    default:
        if (obj.getType()==CardArray::Empty)
            return true;
        if (type==obj.getType()
                && _cardCnt==obj.getN()
                && _maxn>obj.getMaxN())
            return true;
        else return false;
        break;
    }

}

void CardArray::refresh()
{
    type = CardArray::Invalid;
    FOR_TO(0, 19) count[i] = 0;
    FOR_TO(0, _cardCnt)
    switch (_arr[i].toLatin1()) {
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            count[_arr[i].toLatin1() - '0']++;    break;
        case '0':   count[10]++;            break;
        case 'J':   count[11]++;            break;
        case 'Q':   count[12]++;            break;
        case 'K':   count[13]++;            break;
        case 'A':   count[14]++;            break;
        case '2':   count[15]++;            break;
        case '-':   count[16]++;            break;
        case '+':   count[17]++;            break;
        default:                            break;
    }
    FOR_DOWNTO(17, 3)
        if (count[i])
        {
            _maxn = i;
            break;
        }
    switch (_cardCnt) {
    case 1:
        type = CardArray::Single;
        break;
    case 2:
        if (count[_maxn]==2) { type = CardArray::Pair; }
        break;
    case 3:
        if (count[_maxn]==3) { type = CardArray::Triple; }
        break;
    default:
        if (_cardCnt>=4 && _cardCnt <=8)
            if (count[_maxn]==_cardCnt)
            { type = CardArray::Bomb; }
        if (_cardCnt>=5)
            if (isStraight(_maxn-_cardCnt+1, _maxn, 1))
            { type = CardArray::Straight; }
        if (_cardCnt>=6 && _cardCnt%2==0)
            if (isStraight(_maxn-_cardCnt/2+1, _maxn, 2))
            { type = CardArray::StraightPair; }
        if (_cardCnt>=9 && _cardCnt%3==0)
            if (isStraight(_maxn-_cardCnt/3+1, _maxn, 3))
            { type = CardArray::StraightTriple; }
        break;
    }
}

bool CardArray::isStraight(int l, int r, int n) const
{
    if (l<3) return false;
    FOR_TO(l, r) if (count[i]!=n) return false;
    return true;
}

