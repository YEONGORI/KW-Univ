import java.io.FileReader;
import java.util.Scanner;
import java.util.Vector;
class Main {
  public static void main(String args[]) {
    int method = 0;
    Scanner scanner = new Scanner(System.in);
    scanner.useDelimiter(",");

    Vector<String> nameVec = new Vector<String>();
    Vector<String> ageVev = new Vector<String>();
    Vector<String> salaryVev = new Vector<String>();

    String pwd = System.getProperty("user.dir");
    System.out.println(pwd + "\\Salaries.txt");

    // FileReader reader = new FileReader(pwd + "\\Salaries.txt");
    while (scanner.hasNext()) {
      String name = scanner.next();
      String age = scanner.next();
      String salary = scanner.next();

      System.out.println(name);
      System.out.println(age);
      System.out.println(salary);
    }

//     광운,31,2100
// 한울,22,2400
// 비마,21,3000
// 옥의,28,3600
// 문화,40,3100
// 참빛,25,2700
// 누리,23,3000
// 화도,23,2400
// 복지,31,2400
// 새빛,21,3300


    // while(method != 6) {
    //   System.out.println("====================");
    //   System.out.println("1.Load 2.Insert 3.Delete 4.Update 5.Sort 6.Save");
    //   System.out.println("====================");
    //   System.out.print("Selet Method: ");
    //   method = scanner.nextInt();
    //   switch (method) {
    //     case 1:
    //       break;
    //   }
    // }
  }


  // public static ArrayList<String> Load(ArrayList<String> salaries) {
  //   Scanner scanner = new Scanner(new File("/home/runner/testjave/Salaries.txt"));
  //   scanner.useDelimiter(",");
  //   File folder = new File("/home/runner/testjave/");
  //   File files[] = folder.listFiles();

    

  //   int cnt=0;
  //   // for (int i=0;i<files.length;i++) {
  //   //   if (files[i].getName == "Salaries") {
  //   //     cnt++;
  //   //   }
  //   // }

  //   if (cnt == 0 ){
  //     System.out.println("File not exist\n");
  //     return null;
  //   } else {
  //     for (int i=0;i<3;i++) {
  //       salaries.add(scanner.next()); // new line 단위로 읽어낸 뒤에 ,구분자를사용해 따로따로 arraylist 에 저장
  //     }
  //     return salaries;
  //   }

    
  // }
}
