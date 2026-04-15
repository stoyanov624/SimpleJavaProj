package com.shop.model;

import java.time.LocalDate;

public class FoodProduct extends Product {

    private static final long serialVersionUID = 1L;
    private static double foodMarkupPercent = 30.0;

    public FoodProduct(int id, String name, double deliveryPrice, LocalDate expiryDate, int quantity) {
        super(id, name, deliveryPrice, expiryDate, quantity);
    }

    @Override
    public double getMarkupPercent() { return foodMarkupPercent; }

    public static void setFoodMarkupPercent(double percent) { foodMarkupPercent = percent; }
    public static double getFoodMarkupPercent() { return foodMarkupPercent; }

    @Override
    public String toString() { return "[ХРАНА] " + super.toString(); }
}
