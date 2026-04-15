package com.shop.model;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class Receipt implements Serializable {

    private static final long serialVersionUID = 1L;
    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("dd.MM.yyyy HH:mm:ss");
    private static int counter = 1;

    private int receiptNumber;
    private Cashier cashier;
    private LocalDateTime dateTime;
    private List<ReceiptItem> items;
    private double total;

    public Receipt(Cashier cashier, List<ReceiptItem> items, double total) {
        this.receiptNumber = counter++;
        this.cashier = cashier;
        this.dateTime = LocalDateTime.now();
        this.items = items;
        this.total = total;
    }

    public String toFormattedString() {
        StringBuilder sb = new StringBuilder();
        appendHeader(sb);
        appendItems(sb);
        appendFooter(sb);
        return sb.toString();
    }

    private void appendHeader(StringBuilder sb) {
        sb.append("========================================\n");
        sb.append("          КАСОВА БЕЛЕЖКА #").append(receiptNumber).append("\n");
        sb.append("========================================\n");
        sb.append("Касиер : ").append(cashier.getName()).append("\n");
        sb.append("Дата   : ").append(dateTime.format(FORMATTER)).append("\n");
        sb.append("----------------------------------------\n");
    }

    private void appendItems(StringBuilder sb) {
        for (ReceiptItem item : items) {
            sb.append(item).append("\n");
        }
    }

    private void appendFooter(StringBuilder sb) {
        sb.append("----------------------------------------\n");
        sb.append(String.format("ОБЩО: %35.2f лв.%n", total));
        sb.append("========================================\n");
    }

    public int getReceiptNumber() { return receiptNumber; }
    public Cashier getCashier() { return cashier; }
    public LocalDateTime getDateTime() { return dateTime; }
    public List<ReceiptItem> getItems() { return items; }
    public double getTotal() { return total; }

    @Override
    public String toString() { return toFormattedString(); }
}
