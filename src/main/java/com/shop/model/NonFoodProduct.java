package com.shop.model;

import java.time.LocalDate;

public class NonFoodProduct extends Product {

    private static final long serialVersionUID = 1L;
    private static double nonFoodMarkupPercent = 50.0;

    public NonFoodProduct(int id, String name, double deliveryPrice, LocalDate expiryDate, int quantity) {
        super(id, name, deliveryPrice, expiryDate, quantity);
    }

    @Override
    public double getMarkupPercent() { return nonFoodMarkupPercent; }

    public static void setNonFoodMarkupPercent(double percent) { nonFoodMarkupPercent = percent; }
    public static double getNonFoodMarkupPercent() { return nonFoodMarkupPercent; }

    @Override
    public String toString() { return "[НЕ-ХРАНА] " + super.toString(); }
}
