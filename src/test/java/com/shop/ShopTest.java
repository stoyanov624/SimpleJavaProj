package com.shop;

import com.shop.exception.InsufficientFundsException;
import com.shop.exception.InsufficientQuantityException;
import com.shop.model.*;
import com.shop.service.Shop;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.time.LocalDate;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Тестове за основните функционалности на системата.
 */
class ShopTest {

    private Shop shop;
    private Cashier cashier;
    private CashRegister register;

    @BeforeEach
    void setUp() {
        // Конфигурираме надценките преди всеки тест
        FoodProduct.setFoodMarkupPercent(30.0);
        NonFoodProduct.setNonFoodMarkupPercent(50.0);
        Product.setExpiryWarningDays(3);
        Product.setDiscountPercent(20.0);

        shop = new Shop("Тест Магазин");
        cashier = new Cashier(1, "Тест Касиер", 1000.0);
        register = new CashRegister(1, cashier);
        shop.addCashier(cashier);
        shop.addRegister(register);
    }

    // -------------------------------------------------------
    //  Тестове за цени
    // -------------------------------------------------------

    @Test
    @DisplayName("Правилна продажна цена за хранителна стока")
    void testFoodProductSellingPrice() {
        Product milk = new FoodProduct(1, "Мляко", 1.50, LocalDate.now().plusDays(10), 10);
        double expected = 1.50 * 1.30;  // +30% надценка
        assertEquals(expected, milk.getSellingPrice(), 0.01);
    }

    @Test
    @DisplayName("Правилна продажна цена за нехранителна стока")
    void testNonFoodProductSellingPrice() {
        Product shampoo = new NonFoodProduct(2, "Шампоан", 5.00, LocalDate.now().plusDays(100), 5);
        double expected = 5.00 * 1.50;  // +50% надценка
        assertEquals(expected, shampoo.getSellingPrice(), 0.01);
    }

    @Test
    @DisplayName("Намалена цена при наближаващ срок")
    void testNearExpiryDiscount() {
        Product bread = new FoodProduct(3, "Хляб", 0.80, LocalDate.now().plusDays(2), 10);
        double basePrice = 0.80 * 1.30;  // +30% надценка
        double expected = basePrice * 0.80;  // -20% намаление
        assertEquals(expected, bread.getSellingPrice(), 0.01);
    }

    @Test
    @DisplayName("Изтекла стока хвърля изключение")
    void testExpiredProductThrows() {
        Product expired = new FoodProduct(4, "Кисело мляко", 0.90, LocalDate.now().minusDays(1), 5);
        assertThrows(IllegalStateException.class, expired::getSellingPrice);
    }

    @Test
    @DisplayName("isExpired() за изтекла стока")
    void testIsExpired() {
        Product expired = new FoodProduct(5, "Стара стока", 1.00, LocalDate.now().minusDays(1), 1);
        assertTrue(expired.isExpired());
    }

    @Test
    @DisplayName("isNearExpiry() за стока с 2 дни остатък")
    void testIsNearExpiry() {
        Product near = new FoodProduct(6, "Скоро изтичаща", 1.00, LocalDate.now().plusDays(2), 1);
        assertTrue(near.isNearExpiry());
    }

    // -------------------------------------------------------
    //  Тестове за продажби
    // -------------------------------------------------------

    @Test
    @DisplayName("Успешна продажба намалява наличността")
    void testSuccessfulSaleReducesQuantity() throws Exception {
        Product milk = new FoodProduct(1, "Мляко", 1.50, LocalDate.now().plusDays(10), 10);
        shop.deliverProduct(milk);

        List<ReceiptItem> items = List.of(new ReceiptItem(milk, 3));
        register.processSale(items, 100.00);

        assertEquals(7, milk.getQuantity());
    }

    @Test
    @DisplayName("Недостатъчно количество хвърля InsufficientQuantityException")
    void testInsufficientQuantityThrows() {
        Product milk = new FoodProduct(1, "Мляко", 1.50, LocalDate.now().plusDays(10), 2);
        shop.deliverProduct(milk);

        List<ReceiptItem> items = List.of(new ReceiptItem(milk, 10));
        assertThrows(InsufficientQuantityException.class,
                () -> register.processSale(items, 1000.00));
    }

    @Test
    @DisplayName("Недостатъчно пари хвърля InsufficientFundsException")
    void testInsufficientFundsThrows() {
        Product shampoo = new NonFoodProduct(2, "Шампоан", 5.00, LocalDate.now().plusDays(100), 5);
        shop.deliverProduct(shampoo);

        List<ReceiptItem> items = List.of(new ReceiptItem(shampoo, 1));
        assertThrows(InsufficientFundsException.class,
                () -> register.processSale(items, 0.50));  // цената е 7.50, клиентът дава 0.50
    }

    @Test
    @DisplayName("Изтекла стока не може да се продава")
    void testExpiredProductCannotBeSold() {
        Product expired = new FoodProduct(3, "Изтекло", 0.90, LocalDate.now().minusDays(1), 5);
        shop.deliverProduct(expired);

        List<ReceiptItem> items = List.of(new ReceiptItem(expired, 1));
        assertThrows(IllegalStateException.class,
                () -> register.processSale(items, 100.00));
    }

    // -------------------------------------------------------
    //  Тестове за финансов отчет
    // -------------------------------------------------------

    @Test
    @DisplayName("Изчисляване на разходи (заплати + доставки)")
    void testCalculateExpenses() throws Exception {
        // Заплата: 1000 лв.
        // Доставка: 1.50 x 10 = 15 лв.
        Product milk = new FoodProduct(1, "Мляко", 1.50, LocalDate.now().plusDays(10), 10);
        shop.deliverProduct(milk);

        double expected = 1000.0 + 15.0;
        assertEquals(expected, shop.calculateExpenses(), 0.01);
    }

    @Test
    @DisplayName("Изчисляване на приходи след продажба")
    void testCalculateRevenue() throws Exception {
        Product milk = new FoodProduct(1, "Мляко", 1.50, LocalDate.now().plusDays(10), 10);
        shop.deliverProduct(milk);

        List<ReceiptItem> items = List.of(new ReceiptItem(milk, 2));
        register.processSale(items, 100.00);

        double expectedRevenue = 1.50 * 1.30 * 2;  // 2 литра мляко
        assertEquals(expectedRevenue, shop.calculateRevenue(), 0.01);
    }

    @Test
    @DisplayName("Бележката съдържа правилния касиер")
    void testReceiptContainsCashier() throws Exception {
        Product milk = new FoodProduct(1, "Мляко", 1.50, LocalDate.now().plusDays(10), 10);
        shop.deliverProduct(milk);

        List<ReceiptItem> items = List.of(new ReceiptItem(milk, 1));
        Receipt receipt = register.processSale(items, 100.00);

        assertEquals(cashier.getName(), receipt.getCashier().getName());
    }
}
