package com.shop;

import com.shop.exception.InsufficientFundsException;
import com.shop.exception.InsufficientQuantityException;
import com.shop.model.*;
import com.shop.service.ReceiptService;
import com.shop.service.Shop;

import java.time.LocalDate;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        System.out.println("=== СИСТЕМА ЗА УПРАВЛЕНИЕ НА МАГАЗИН ===\n");

        configureMarkups();
        Shop shop = buildShop();
        deliverProducts(shop);
        printAvailableProducts(shop);
        runSaleScenarios(shop);
        demonstrateSerialization(shop);
        shop.printFinancialReport();
    }

    private static void configureMarkups() {
        FoodProduct.setFoodMarkupPercent(30.0);
        NonFoodProduct.setNonFoodMarkupPercent(50.0);
        Product.setExpiryWarningDays(3);
        Product.setDiscountPercent(20.0);
    }

    private static Shop buildShop() {
        Shop shop = new Shop("Супермаркет Примерен");

        Cashier cashier1 = new Cashier(1, "Иван Петров", 1500.00);
        Cashier cashier2 = new Cashier(2, "Мария Георгиева", 1400.00);
        shop.addCashier(cashier1);
        shop.addCashier(cashier2);

        shop.addRegister(new CashRegister(1, cashier1));
        shop.addRegister(new CashRegister(2, cashier2));

        return shop;
    }

    private static void deliverProducts(Shop shop) {
        shop.deliverProduct(new FoodProduct(1, "Прясно мляко 1л", 1.50, LocalDate.now().plusDays(10), 50));
        shop.deliverProduct(new FoodProduct(2, "Хляб Добруджа", 0.80, LocalDate.now().plusDays(2), 30));
        shop.deliverProduct(new NonFoodProduct(3, "Шампоан Pantene 400мл", 5.00, LocalDate.now().plusDays(365), 20));
        shop.deliverProduct(new FoodProduct(4, "Кисело мляко 400г", 0.90, LocalDate.now().minusDays(1), 5));
    }

    private static void printAvailableProducts(Shop shop) {
        System.out.println("\n--- Налични стоки ---");
        shop.getAvailableProducts().forEach(System.out::println);
    }

    private static void runSaleScenarios(Shop shop) {
        Product milk = shop.findProductById(1);
        Product bread = shop.findProductById(2);
        Product shampoo = shop.findProductById(3);
        Product expiredYogurt = shop.findProductById(4);

        CashRegister reg1 = shop.getRegisters().get(0);
        CashRegister reg2 = shop.getRegisters().get(1);

        // Успешна продажба
        System.out.println("\n--- Продажба #1 (успешна) ---");
        trySale(reg1, List.of(new ReceiptItem(milk, 2), new ReceiptItem(bread, 1), new ReceiptItem(shampoo, 1)), 20.00);

        // Недостатъчно пари
        System.out.println("\n--- Продажба #2 (недостатъчно пари) ---");
        trySale(reg2, List.of(new ReceiptItem(milk, 5), new ReceiptItem(shampoo, 3)), 1.00);

        // Недостатъчно количество
        System.out.println("\n--- Продажба #3 (недостатъчно количество) ---");
        trySale(reg1, List.of(new ReceiptItem(milk, 999)), 9999.00);

        // Изтекла стока
        System.out.println("\n--- Продажба #4 (изтекъл срок) ---");
        trySale(reg1, List.of(new ReceiptItem(expiredYogurt, 1)), 50.00);
    }

    private static void trySale(CashRegister register, List<ReceiptItem> items, double money) {
        try {
            Receipt receipt = register.processSale(items, money);
            System.out.println(receipt);
        } catch (InsufficientQuantityException | InsufficientFundsException | IllegalStateException e) {
            System.err.println("Уловено изключение: " + e.getMessage());
        }
    }

    private static void demonstrateSerialization(Shop shop) {
        System.out.println("\n--- Сериализация и четене от файл ---");
        List<Receipt> receipts = shop.getRegisters().get(0).getIssuedReceipts();
        if (receipts.isEmpty()) return;

        ReceiptService service = new ReceiptService();
        Receipt receipt = receipts.get(0);

        service.serialize(receipt);
        Receipt loaded = service.deserialize(receipt.getReceiptNumber());
        if (loaded != null) {
            System.out.println("Заредена бележка #" + loaded.getReceiptNumber());
        }

        System.out.println(service.readFromFile(receipt.getReceiptNumber()));
    }
}
