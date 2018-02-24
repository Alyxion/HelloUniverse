//
//  MainScreen.swift
//  HelloSwiftWorld
//
//  Created by Michael Ikemann on 24.02.18.
//  Copyright © 2018 MI. All rights reserved.
//

import UIKit

class MainScreenController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        self.view = UIView();
        
        self.view!.backgroundColor = UIColor.white;

        let label = UITextView();
        label.text = "Hello world"
        label.textColor = UIColor.black;
        label.font = UIFont(name: "Arial", size: 40.0)
        label.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        
        self.view.addSubview(label);

        label.frame = CGRect(x: 40.0, y: 40.0, width: label.frame.size.width, height: label.frame.size.height)
        
        let testButton = UIButton()
        testButton.backgroundColor = UIColor.lightGray
        testButton.setTitleColor(UIColor.red, for: UIControlState.normal)
        testButton.setTitle("Click me please", for: UIControlState.normal)
        testButton.layer.cornerRadius = 5
        testButton.layer.borderWidth = 1
        testButton.layer.borderColor = UIColor.black.cgColor
        
        let minSize = testButton.sizeThatFits(CGSize(width: 20.0, height: CGFloat.greatestFiniteMagnitude))
        
        testButton.frame = CGRect(origin: CGPoint(x: 40.0, y: 120.0), size: CGSize(width: minSize.width+10.0, height: minSize.height))
        
        testButton.addTarget(self, action: #selector(handleButtonPress(button:)), for: .touchUpInside)
        
        self.view.addSubview(testButton)
    }
    
    @objc
    func handleButtonPress(button: UIButton!)
    {
        let alert = UIAlertController(title: "Hello world!", message: "How are you doing?", preferredStyle: UIAlertControllerStyle.alert)
        present(alert, animated: false, completion: nil)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
