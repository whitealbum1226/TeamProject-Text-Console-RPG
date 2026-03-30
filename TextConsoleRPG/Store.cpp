// Store.cpp

#include "Store.h"
#include "Player.h"
#include "Inventory.h"

Store::Store()
    : isOpen_(false)
{
    // 고정 가격 아이템 목록
    shopItems_.push_back({ "빨간 포션", 30 });
    shopItems_.push_back({ "파란 포션", 30 });
    shopItems_.push_back({ "공격의 영약", 50 });
    shopItems_.push_back({ "방어의 영약", 50 });
}

// Store는 UI/로그를 담당하지 않고, 상태만 관리하게 기초 설계함
// 출력은 게임 로그 시스템에서 처리하도록 분리 해둠
// 혹시 담당 파트에서 무리가 된다 싶으면 협의 후 수정
void Store::Open()
{
    isOpen_ = true;
}

void Store::Close()
{
    isOpen_ = false;
}

bool Store::IsOpen() const // 상점이 열려있는지 상태 체크용
{
    return isOpen_;
}

const std::vector<ShopItem>& Store::GetShopItems() const
{
    return shopItems_;
}

// 플레이어와 인벤토리와 함수명을 맞춰서 변경 예정
StoreResult Store::BuyItem(int index, Player& player, Inventory& inventory)
{
    if (!isOpen_)
    {
        return StoreResult::StoreClosed;
    }

    if (index < 0 || index >= static_cast<int>(shopItems_.size()))
    {
        return StoreResult::InvalidIndex;
    }

    const ShopItem& item = shopItems_[index];

    if (player.GetGold() < item.price)
    {
        return StoreResult::NotEnoughGold;
    }

    player.loseGold(item.price);

    // 인벤토리에 함수명 맞게 변경하면됨
    inventory.AddItem(item.name, item.price);

    // 아이템 구매 처리 로직 설명
    // 1. 상점 상태 확인
    // 2. 상점 아이템 인덱스 유효성 검사
    // 3. 골드 충분 여부 확인
    // 4. 골드 차감 후 인벤토리에 아이템 추가 로직
    return StoreResult::Success;
}

StoreResult Store::SellItem(int index, Player& player, Inventory& inventory)
{
    if (!isOpen_)
    {
        return StoreResult::StoreClosed;
    }

    if (inventory.GetItemCount() == 0)
    {
        return StoreResult::InventoryEmpty;
    }

    if (index < 0 || index >= inventory.GetItemCount())
    {
        return StoreResult::InvalidIndex;
    }

    // 인벤토리에서 꺼낸 아이템이 name, price를 가진다고 가정
    // 없으면 추가 or 변경
    auto item = inventory.GetItem(index);
    // 판매 가격ㅇ느 구입 원가의 60%로 계산
    // 가격 밸런스 조정 필요시 해당 비율 수정
    int sellPrice = item.price * 60 / 100;

    // 아래 함수 순서 변경 X
    // 인벤토리 제거 -> 골드 지급 순임
    inventory.RemoveItem(index);
    player.gainGold(sellPrice);

    // 해당부분은 다른곳에서 배워왔음!
    // 결과 상태를 세분화하여 UI 파트에서 상황별 처리가 가능하도록 설계
    return StoreResult::Success;
}
