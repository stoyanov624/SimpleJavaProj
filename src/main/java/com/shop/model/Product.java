package com.shop.model;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

/**
 * Базов клас за всяка стока в магазина.
 * Съдържа общите полета и логиката за изчисляване на продажна цена.
 */
public abstract class Product implements Serializable {

    private static final long serialVersionUID = 1L;

    private int id;
    private String name;
    private double deliveryPrice;   // доставна цена
    private LocalDate expiryDate;   // срок на годност
    private int quantity;           // наличност

    // Колко дни преди изтичане стоката се счита за "наближаваща"
    private static int expiryWarningDays = 3;

    // Процент намаление при наближаваща годност
    private static double discountPercent = 20.0;

    public Product(int id, String name, double deliveryPrice, LocalDate expiryDate, int quantity) {
        this.id = id;
        this.name = name;
        this.deliveryPrice = deliveryPrice;
        this.expiryDate = expiryDate;
        this.quantity = quantity;
    }

    /**
     * Всяка подкласа дефинира собствен процент надценка.
     */
    public abstract double getMarkupPercent();

    /**
     * Изчислява продажната цена:
     * 1. Ако стоката е изтекла → хвърля изключение (не се продава)
     * 2. Ако наближава срокът → прилага намаление
     * 3. Иначе → доставна цена + надценка
     */
    public double getSellingPrice() {
        if (isExpired()) {
            throw new IllegalStateException("Стока '" + name + "' е с изтекъл срок на годност и не може да се продава.");
        }

        double basePrice = deliveryPrice * (1 + getMarkupPercent() / 100.0);

        if (isNearExpiry()) {
            basePrice = basePrice * (1 - discountPercent / 100.0);
        }

        return Math.round(basePrice * 100.0) / 100.0;
    }

    /**
     * Проверява дали стоката е изтекла.
     */
    public boolean isExpired() {
        return LocalDate.now().isAfter(expiryDate);
    }

    /**
     * Проверява дали стоката наближава края на срока си.
     */
    public boolean isNearExpiry() {
        long daysLeft = ChronoUnit.DAYS.between(LocalDate.now(), expiryDate);
        return daysLeft >= 0 && daysLeft <= expiryWarningDays;
    }

    // --- Getters и Setters ---

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
        return String.format("[%d] %s | Дост. цена: %.2f | Прод. цена: %.2f | Годен до: %s | Кол: %d",
                id, name, deliveryPrice, isExpired() ? 0 : getSellingPrice(), expiryDate, quantity);
    }
}
