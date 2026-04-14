package com.shop.exception;

/**
 * Изключение при недостатъчно пари от страна на клиента.
 */
public class InsufficientFundsException extends Exception {

    private final double provided;
    private final double required;

    public InsufficientFundsException(double provided, double required) {
        super(String.format(
                "Недостатъчно пари. Необходими: %.2f лв., предоставени: %.2f лв.",
                required, provided
        ));
        this.provided = provided;
        this.required = required;
    }

    public double getProvided() { return provided; }
    public double getRequired() { return required; }
}
