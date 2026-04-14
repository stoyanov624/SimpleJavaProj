package com.shop.service;

import com.shop.model.*;

import java.util.ArrayList;
import java.util.List;

/**
 * Главният клас "Магазин".
 * Управлява касиери, стоки, каси и бележки.
 * Изчислява финансови показатели.
 */
public class Shop {

    private String name;

    // Всички касиери в магазина
    private List<Cashier> cashiers;

    // Всички каси в магазина
    private List<CashRegister> registers;

    // Доставени стоки (инвентар)
    private List<Product> deliveredProducts;

    // Всички издадени касови бележки
    private List<Receipt> allReceipts;

    // Обща стойност на доставките (за изчисляване на разходи)
    private double totalDeliveryCost;

    public Shop(String name) {
        this.name = name;
        this.cashiers = new ArrayList<>();
        this.registers = new ArrayList<>();
        this.deliveredProducts = new ArrayList<>();
        this.allReceipts = new ArrayList<>();
        this.totalDeliveryCost = 0;
    }

    // =====================
    //   УПРАВЛЕНИЕ НА ПЕРСОНАЛ
    // =====================

    public void addCashier(Cashier cashier) {
        cashiers.add(cashier);
        System.out.println("Добавен касиер: " + cashier.getName());
    }

    public void addRegister(CashRegister register) {
        registers.add(register);
        System.out.println("Добавена каса #" + register.getId());
    }

    // =====================
    //   УПРАВЛЕНИЕ НА СТОКИ
    // =====================

    /**
     * Добавя доставена стока.
     * Добавя и стойността на доставката към общите разходи.
     */
    public void deliverProduct(Product product) {
        deliveredProducts.add(product);
        totalDeliveryCost += product.getDeliveryPrice() * product.getQuantity();
        System.out.println("Доставена стока: " + product.getName() + " x" + product.getQuantity());
    }

    /**
     * Търси стока по ID.
     */
    public Product findProductById(int id) {
        return deliveredProducts.stream()
                .filter(p -> p.getId() == id)
                .findFirst()
                .orElse(null);
    }

    /**
     * Списък с наличните (не изтекли) стоки.
     */
    public List<Product> getAvailableProducts() {
        return deliveredProducts.stream()
                .filter(p -> !p.isExpired() && p.getQuantity() > 0)
                .toList();
    }

    // =====================
    //   ФИНАНСОВИ ИЗЧИСЛЕНИЯ
    // =====================

    /**
     * Общи разходи = заплати + стойност на доставките
     */
    public double calculateExpenses() {
        double salaries = cashiers.stream()
                .mapToDouble(Cashier::getMonthlySalary)
                .sum();
        return salaries + totalDeliveryCost;
    }

    /**
     * Приходи = сбор от всички издадени бележки
     */
    public double calculateRevenue() {
        // Събираме от всички каси
        double total = 0;
        for (CashRegister register : registers) {
            for (Receipt receipt : register.getIssuedReceipts()) {
                total += receipt.getTotal();
            }
        }
        return Math.round(total * 100.0) / 100.0;
    }

    /**
     * Печалба = приходи - разходи
     */
    public double calculateProfit() {
        return Math.round((calculateRevenue() - calculateExpenses()) * 100.0) / 100.0;
    }

    /**
     * Отпечатва финансов отчет.
     */
    public void printFinancialReport() {
        System.out.println("\n========================================");
        System.out.println("   ФИНАНСОВ ОТЧЕТ: " + name);
        System.out.println("========================================");
        System.out.printf("Разходи     : %10.2f лв.%n", calculateExpenses());
        System.out.printf("Приходи     : %10.2f лв.%n", calculateRevenue());
        System.out.printf("Печалба     : %10.2f лв.%n", calculateProfit());
        System.out.println("========================================\n");
    }

    // --- Getters ---

    public String getName() { return name; }
    public List<Cashier> getCashiers() { return cashiers; }
    public List<CashRegister> getRegisters() { return registers; }
    public List<Product> getDeliveredProducts() { return deliveredProducts; }
    public double getTotalDeliveryCost() { return totalDeliveryCost; }
}
