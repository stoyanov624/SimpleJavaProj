package com.shop.exception;

import com.shop.model.Product;

/**
 * Изключение при недостатъчно количество на стока.
 * Хвърля се когато клиент иска повече от наличното.
 */
public class InsufficientQuantityException extends Exception {

    private final Product product;
    private final int requested;

    public InsufficientQuantityException(Product product, int requested) {
        super(String.format(
                "Недостатъчно количество за стока '%s' (ID: %d). " +
                "Заявено: %d, налично: %d.",
                product.getName(), product.getId(), requested, product.getQuantity()
        ));
        this.product = product;
        this.requested = requested;
    }

    public Product getProduct() { return product; }
    public int getRequested() { return requested; }
    public int getAvailable() { return product.getQuantity(); }
}
