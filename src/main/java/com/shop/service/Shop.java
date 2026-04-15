package com.shop.service;

import com.shop.model.*;

import java.util.ArrayList;
import java.util.List;

public class Shop {

    private String name;
    private List<Cashier> cashiers;
    private List<CashRegister> registers;
    private List<Product> deliveredProducts;
    private double totalDeliveryCost;

    public Shop(String name) {
        this.name = name;
        this.cashiers = new ArrayList<>();
        this.registers = new ArrayList<>();
        this.deliveredProducts = new ArrayList<>();
        this.totalDeliveryCost = 0;
    }

    public void addCashier(Cashier cashier) {
        cashiers.add(cashier);
        System.out.println("Добавен касиер: " + cashier.getName());
    }

    public void addRegister(CashRegister register) {
        registers.add(register);
        System.out.println("Добавена каса #" + register.getId());
    }

    public void deliverProduct(Product product) {
        deliveredProducts.add(product);
        totalDeliveryCost += product.getDeliveryPrice() * product.getQuantity();
        System.out.println("Доставена стока: " + product.getName() + " x" + product.getQuantity());
    }

    public Product findProductById(int id) {
        return deliveredProducts.stream()
                .filter(p -> p.getId() == id)
                .findFirst()
                .orElse(null);
    }

    public List<Product> getAvailableProducts() {
        return deliveredProducts.stream()
                .filter(p -> !p.isExpired() && p.getQuantity() > 0)
                .toList();
    }

    public double calculateExpenses() {
        return sumSalaries() + totalDeliveryCost;
    }

    public double calculateRevenue() {
        double total = registers.stream()
                .flatMap(r -> r.getIssuedReceipts().stream())
                .mapToDouble(Receipt::getTotal)
                .sum();
        return Math.round(total * 100.0) / 100.0;
    }

    public double calculateProfit() {
        return Math.round((calculateRevenue() - calculateExpenses()) * 100.0) / 100.0;
    }

    public void printFinancialReport() {
        System.out.println("\n========================================");
        System.out.println("   ФИНАНСОВ ОТЧЕТ: " + name);
        System.out.println("========================================");
        System.out.printf("Разходи : %10.2f лв.%n", calculateExpenses());
        System.out.printf("Приходи : %10.2f лв.%n", calculateRevenue());
        System.out.printf("Печалба : %10.2f лв.%n", calculateProfit());
        System.out.println("========================================\n");
    }

    private double sumSalaries() {
        return cashiers.stream().mapToDouble(Cashier::getMonthlySalary).sum();
    }

    public String getName() { return name; }
    public List<Cashier> getCashiers() { return cashiers; }
    public List<CashRegister> getRegisters() { return registers; }
    public List<Product> getDeliveredProducts() { return deliveredProducts; }
    public double getTotalDeliveryCost() { return totalDeliveryCost; }
}
