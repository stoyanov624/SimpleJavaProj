package com.shop.model;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

/**
 * Касова бележка.
 * Съдържа: пореден номер, касиер, дата/час, стоки и обща сума.
 * Имплементира Serializable, за да може да се сериализира/десериализира.
 */
public class Receipt implements Serializable {

    private static final long serialVersionUID = 1L;

    // Статичен брояч — увеличава се при всяка нова бележка
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

    public int getReceiptNumber() { return receiptNumber; }
    public Cashier getCashier() { return cashier; }
    public LocalDateTime getDateTime() { return dateTime; }
    public List<ReceiptItem> getItems() { return items; }
    public double getTotal() { return total; }

    /**
     * Форматира бележката като текст за запис във файл или показване на екрана.
     */
    public String toFormattedString() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy HH:mm:ss");
        StringBuilder sb = new StringBuilder();

        sb.append("========================================\n");
        sb.append("          КАСОВА БЕЛЕЖКА #").append(receiptNumber).append("\n");
        sb.append("========================================\n");
        sb.append("Касиер : ").append(cashier.getName()).append("\n");
        sb.append("Дата   : ").append(dateTime.format(formatter)).append("\n");
        sb.append("----------------------------------------\n");

        for (ReceiptItem item : items) {
            sb.append(item.toString()).append("\n");
        }

        sb.append("----------------------------------------\n");
        sb.append(String.format("ОБЩО: %35.2f лв.%n", total));
        sb.append("========================================\n");

        return sb.toString();
    }

    @Override
    public String toString() {
        return toFormattedString();
    }
}
