package com.shop.model;

import com.shop.exception.InsufficientFundsException;
import com.shop.exception.InsufficientQuantityException;
import com.shop.service.ReceiptService;

import java.util.ArrayList;
import java.util.List;

public class CashRegister {

    private int id;
    private Cashier cashier;
    private List<Receipt> issuedReceipts;
    private ReceiptService receiptService;

    public CashRegister(int id, Cashier cashier) {
        this.id = id;
        this.cashier = cashier;
        this.issuedReceipts = new ArrayList<>();
        this.receiptService = new ReceiptService();
    }

    public Receipt processSale(List<ReceiptItem> items, double clientMoney)
            throws InsufficientQuantityException, InsufficientFundsException {

        validateItems(items);

        double total = calculateTotal(items);
        if (clientMoney < total) {
            throw new InsufficientFundsException(clientMoney, total);
        }

        deductQuantities(items);

        Receipt receipt = new Receipt(cashier, items, total);
        receiptService.saveToFile(receipt);
        issuedReceipts.add(receipt);

        return receipt;
    }

    private void validateItems(List<ReceiptItem> items) throws InsufficientQuantityException {
        for (ReceiptItem item : items) {
            Product product = item.getProduct();
            if (product.isExpired()) {
                throw new IllegalStateException("Стока '" + product.getName() + "' е с изтекъл срок.");
            }
            if (product.getQuantity() < item.getQuantity()) {
                throw new InsufficientQuantityException(product, item.getQuantity());
            }
        }
    }

    private double calculateTotal(List<ReceiptItem> items) {
        double total = 0;
        for (ReceiptItem item : items) {
            total += item.getProduct().getSellingPrice() * item.getQuantity();
        }
        return Math.round(total * 100.0) / 100.0;
    }

    private void deductQuantities(List<ReceiptItem> items) {
        for (ReceiptItem item : items) {
            Product p = item.getProduct();
            p.setQuantity(p.getQuantity() - item.getQuantity());
        }
    }

    public int getId() { return id; }
    public Cashier getCashier() { return cashier; }
    public List<Receipt> getIssuedReceipts() { return issuedReceipts; }

    @Override
    public String toString() {
        return String.format("Каса #%d | Касиер: %s", id, cashier.getName());
    }
}
