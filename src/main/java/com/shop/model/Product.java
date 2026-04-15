package com.shop.model;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

public abstract class Product implements Serializable {

    private static final long serialVersionUID = 1L;

    private int id;
    private String name;
    private double deliveryPrice;
    private LocalDate expiryDate;
    private int quantity;

    private static int expiryWarningDays = 3;
    private static double discountPercent = 20.0;

    public Product(int id, String name, double deliveryPrice, LocalDate expiryDate, int quantity) {
        this.id = id;
        this.name = name;
        this.deliveryPrice = deliveryPrice;
        this.expiryDate = expiryDate;
        this.quantity = quantity;
    }

    // Всяка подкласа задава собствена надценка
    public abstract double getMarkupPercent();

    public double getSellingPrice() {
        if (isExpired()) {
            throw new IllegalStateException("Стока '" + name + "' е с изтекъл срок.");
        }
        double price = applyMarkup();
        if (isNearExpiry()) {
            price = applyDiscount(price);
        }
        return round(price);
    }

    public boolean isExpired() {
        return LocalDate.now().isAfter(expiryDate);
    }

    public boolean isNearExpiry() {
        long daysLeft = ChronoUnit.DAYS.between(LocalDate.now(), expiryDate);
        return daysLeft >= 0 && daysLeft <= expiryWarningDays;
    }

    private double applyMarkup() {
        return deliveryPrice * (1 + getMarkupPercent() / 100.0);
    }

    private double applyDiscount(double price) {
        return price * (1 - discountPercent / 100.0);
    }

    private double round(double value) {
        return Math.round(value * 100.0) / 100.0;
    }

    public int getId() { return id; }
    public String getName() { return name; }
    public double getDeliveryPrice() { return deliveryPrice; }
    public LocalDate getExpiryDate() { return expiryDate; }
    public int getQuantity() { return quantity; }
    public void setQuantity(int quantity) { this.quantity = quantity; }

    public static void setExpiryWarningDays(int days) { expiryWarningDays = days; }
    public static void setDiscountPercent(double percent) { discountPercent = percent; }
    public static int getExpiryWarningDays() { return expiryWarningDays; }
    public static double getDiscountPercent() { return discountPercent; }

    @Override
    public String toString() {
        return String.format("[%d] %s | Дост: %.2f | Прод: %.2f | Годен до: %s | Кол: %d",
                id, name, deliveryPrice, isExpired() ? 0 : getSellingPrice(), expiryDate, quantity);
    }
}
