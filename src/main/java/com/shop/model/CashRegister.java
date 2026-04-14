package com.shop.model;

import com.shop.exception.InsufficientFundsException;
import com.shop.exception.InsufficientQuantityException;
import com.shop.service.ReceiptService;

import java.util.ArrayList;
import java.util.List;

/**
 * Касов апарат в магазина.
 * На всяка каса работи точно един касиер.
 * Касата обработва продажби и издава касови бележки.
 */
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

    /**
     * Обработва покупка.
     *
     * @param items        — списък с артикули (стока + количество)
     * @param clientMoney  — пари на клиента
     * @return издадената касова бележка
     * @throws InsufficientQuantityException ако няма достатъчно стока
     * @throws InsufficientFundsException    ако клиентът няма достатъчно пари
     */
    public Receipt processSale(List<ReceiptItem> items, double clientMoney)
            throws InsufficientQuantityException, InsufficientFundsException {

        // 1. Проверяваме наличността и изчисляваме тотала
        double total = 0;
        for (ReceiptItem item : items) {
            Product product = item.getProduct();

            if (product.isExpired()) {
                throw new IllegalStateException(
                        "Стока '" + product.getName() + "' е с изтекъл срок и не може да се продава.");
            }

            if (product.getQuantity() < item.getQuantity()) {
                throw new InsufficientQuantityException(product, item.getQuantity());
            }

            total += product.getSellingPrice() * item.getQuantity();
        }

        // 2. Проверяваме дали клиентът има достатъчно пари
        total = Math.round(total * 100.0) / 100.0;
        if (clientMoney < total) {
            throw new InsufficientFundsException(clientMoney, total);
        }

        // 3. Намаляваме наличностите
        for (ReceiptItem item : items) {
            Product product = item.getProduct();
            product.setQuantity(product.getQuantity() - item.getQuantity());
        }

        // 4. Създаваме и записваме касовата бележка
        Receipt receipt = new Receipt(cashier, items, total);
        receiptService.saveToFile(receipt);
        issuedReceipts.add(receipt);

        return receipt;
    }

    public int getId() { return id; }
    public Cashier getCashier() { return cashier; }
    public List<Receipt> getIssuedReceipts() { return issuedReceipts; }

    @Override
    public String toString() {
        return String.format("Каса #%d | Касиер: %s", id, cashier.getName());
    }
}
