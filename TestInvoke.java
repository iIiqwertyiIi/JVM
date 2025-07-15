public class TestInvoke {
    public static void main(String[] args) {
        TestInvoke test = new TestInvoke();
        test.instanceMethod();  // invokevirtual
        staticMethod();         // invokestatic
        test.constructor();     // invokespecial
    }
    
    public void instanceMethod() {
        System.out.println("Instance method called");
    }
    
    public static void staticMethod() {
        System.out.println("Static method called");
    }
    
    public void constructor() {
        // Simula chamada de construtor
        System.out.println("Constructor-like method called");
    }
} 