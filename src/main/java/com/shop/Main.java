package com.shop;

import com.shop.exception.InsufficientFundsException;
import com.shop.exception.InsufficientQuantityException;
import com.shop.model.*;
import com.shop.service.ReceiptService;
import com.shop.service.Shop;

import java.time.LocalDate;
import java.util.List;

/**
 * Главна точка на влизане в програмата.
 * Демонстрира всички функционалности на системата.
 */
public class Main {

    public static void main(String[] args) {

        System.out.println("=== СИСТЕМА ЗА УПРАВЛЕНИЕ НА МАГАЗИН ===\n");

        // -------------------------------------------------------
        // 1. Конфигурация на надценките и намаленията
        // -------------------------------------------------------
        FoodProduct.setFoodMarkupPercent(30.0);          // +30% за хранителни
        NonFoodProduct.setNonFoodMarkupPercent(50.0);    // +50% за нехранителни
        Product.setExpiryWarningDays(3);                  // предупреждение 3 дни преди
        Product.setDiscountPercent(20.0);                 // 20% намаление при наближаване

        // -------------------------------------------------------
        // 2. Създаване на магазина
        // -------------------------------------------------------
        Shop shop = new Shop("Супермаркет Примерен");

        // -------------------------------------------------------
        // 3. Добавяне на касиери и каси
        // -------------------------------------------------------
        Cashier cashier1 = new Cashier(1, "Иван Петров", 1500.00);
        Cashier cashier2 = new Cashier(2, "Мария Георгиева", 1400.00);
        shop.addCashier(cashier1);
        shop.addCashier(cashier2);

        CashRegister register1 = new CashRegister(1, cashier1);
        CashRegister register2 = new CashRegister(2, cashier2);
        shop.addRegister(register1);
        shop.addRegister(register2);

        // -------------------------------------------------------
        // 4. Доставка на стоки
        // -------------------------------------------------------
        // Нормална хранителна стока
        Product milk = new FoodProduct(1, "Прясно мляко 1л", 1.50, LocalDate.now().plusDays(10), 50);

        // Стока с наближаващ срок (→ ще получи намаление)
        Product bread = new FoodProduct(2, "Хляб Добруджа", 0.80, LocalDate.now().plusDays(2), 30);

        // Нехранителна стока
        Product shampoo = new NonFoodProduct(3, "Шампоан Pantene 400мл", 5.00, LocalDate.now().plusDays(365), 20);

        // Стока с изтекъл срок (не може да се продава)
        Product expiredYogurt = new FoodProduct(4, "Кисело мляко 400г", 0.90, LocalDate.now().minusDays(1), 5);

        shop.deliverProduct(milk);
        shop.deliverProduct(bread);
        shop.deliverProduct(shampoo);
        shop.deliverProduct(expiredYogurt);

        // -------------------------------------------------------
        // 5. Показване на наличните стоки
        // -------------------------------------------------------
        System.out.println("\n--- Налични стоки ---");
        for (Product p : shop.getAvailableProducts()) {
            System.out.println(p);
        }

        // -------------------------------------------------------
        // 6. Успешна продажба
        // -------------------------------------------------------
        System.out.println("\n--- Продажба #1 (успешна) ---");
        try {
            List<ReceiptItem> items1 = List.of(
                    new ReceiptItem(milk, 2),
                    new ReceiptItem(bread, 1),
                    new ReceiptItem(shampoo, 1)
            );
            Receipt receipt1 = register1.processSale(items1, 20.00);
            System.out.println(receipt1);
        } catch (InsufficientQuantityException | InsufficientFundsException e) {
            System.err.println("Грешка: " + e.getMessage());
        }

        // -------------------------------------------------------
        // 7. Продажба с недостатъчни пари
        // -------------------------------------------------------
        System.out.println("--- Продажба #2 (недостатъчно пари) ---");
        try {
            List<ReceiptItem> items2 = List.of(
                    new ReceiptItem(milk, 5),
                    new ReceiptItem(shampoo, 3)
            );
            register2.processSale(items2, 1.00);  // само 1 лев — ще гръмне
        } catch (InsufficientFundsException e) {
            System.err.println("Уловено изключение: " + e.getMessage());
        } catch (InsufficientQuantityException e) {
            System.err.println("Уловено изключение: " + e.getMessage());
        }

        // -------------------------------------------------------
        // 8. Продажба с недостатъчно количество
        // -------------------------------------------------------
        System.out.println("\n--- Продажба #3 (недостатъчно количество) ---");
        try {
            List<ReceiptItem> items3 = List.of(
                    new ReceiptItem(milk, 999)  // 999 — много повече от наличното
            );
            register1.processSale(items3, 9999.00);
        } catch (InsufficientQuantityException e) {
            System.err.println("Уловено изключение: " + e.getMessage());
        } catch (InsufficientFundsException e) {
            System.err.println("Уловено изключение: " + e.getMessage());
        }

        // -------------------------------------------------------
        // 9. Опит за продажба на изтекла стока
        // -------------------------------------------------------
        System.out.println("\n--- Продажба #4 (изтекъл срок) ---");
        try {
            List<ReceiptItem> items4 = List.of(
                    new ReceiptItem(expiredYogurt, 1)
            );
            register1.processSale(items4, 50.00);
        } catch (IllegalStateException e) {
            System.err.println("Уловено изключение: " + e.getMessage());
        } catch (InsufficientQuantityException | InsufficientFundsException e) {
            System.err.println("Уловено изключение: " + e.getMessage());
        }

        // -------------------------------------------------------
        // 10. Сериализация и десериализация на бележка
        // -------------------------------------------------------
        System.out.println("\n--- Сериализация и десериализация ---");
        ReceiptService receiptService = new ReceiptService();
        List<Receipt> receipts = register1.getIssuedReceipts();
        if (!receipts.isEmpty()) {
            Receipt first = receipts.get(0);
            receiptService.serialize(first);

            Receipt loaded = receiptService.deserialize(first.getReceiptNumber());
            if (loaded != null) {
                System.out.println("Успешно заредена бележка #" + loaded.getReceiptNumber());
            }
        }

        // -------------------------------------------------------
        // 11. Четене на бележка от текстов файл
        // -------------------------------------------------------
        System.out.println("\n--- Четене на бележка от файл ---");
        if (!receipts.isEmpty()) {
            String content = receiptService.readFromFile(receipts.get(0).getReceiptNumber());
            System.out.println(content);
        }

        // -------------------------------------------------------
        // 12. Финансов отчет
        // -------------------------------------------------------
        shop.printFinancialReport();
    }
}
