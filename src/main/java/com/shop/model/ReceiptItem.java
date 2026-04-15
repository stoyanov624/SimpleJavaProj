package com.shop.model;

import java.io.Serializable;

public class ReceiptItem implements Serializable {

    private static final long serialVersionUID = 1L;

    private Product product;
    private int quantity;
    private double unitPrice;

    public ReceiptItem(Product product, int quantity) {
        this.product = product;
        this.quantity = quantity;
        this.unitPrice = product.getSellingPrice();
    }

    public Product getProduct() { return product; }
    public int getQuantity() { return quantity; }
    public double getUnitPrice() { return unitPrice; }
    public double getLineTotal() { return Math.round(unitPrice * quantity * 100.0) / 100.0; }

    @Override
    public String toString() {
        return String.format("  %-25s %5d бр. x %7.2f лв. = %8.2f лв.",
                product.getName(), quantity, unitPrice, getLineTotal());
    }
}
