abstract class Figure {
    double d1, d2;

    Figure(double a, double b) {
        this.d1 = a;
        this.d2 = b;
    }
}

public class Problem1 {
    public static void main(String[] args) {
        Rectangle r = new Rectangle(9, 5);
        Triangle t = new Triangle(10, 8);

        Figure ref;

        ref = r;
        System.out.println("Area: " + ref.area()); // 45 

        ref = t;
        System.out.println("Area: " + ref.area()); // 40
    }
}
