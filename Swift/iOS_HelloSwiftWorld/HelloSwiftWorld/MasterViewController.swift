//
//  MasterViewController.swift
//  HelloSwiftWorld
//
//  Created by Michael Ikemann on 24.02.18.
//  Copyright © 2018 Michael Ikemann. All rights reserved.
//

import UIKit

class MasterViewController: UITableViewController
{

    var sections: NSMutableArray? = nil

    //! Selects the screen at given index
    /** @param [in] index The new index */
    func selectScreen(index: Int)
    {
        if let splitc = splitViewController
        {
            guard let leftNavController = splitc.viewControllers.first as? UINavigationController,
            let masterViewController = leftNavController.topViewController as? MasterViewController
                else { fatalError() }
            
            let msc = MainScreenController()
            
            masterViewController.showDetailViewController(msc, sender: self)
        }
    }

    override func viewDidLoad()
    {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        navigationItem.leftBarButtonItem = editButtonItem

        sections = NSMutableArray()
        
        if let seclist = sections
        {
            seclist.add("Main Screen")
            seclist.add("User List")
            seclist.add("About")
        }
        
        selectScreen(index: 0)
    }

    override func viewWillAppear(_ animated: Bool) {
        clearsSelectionOnViewWillAppear = splitViewController!.isCollapsed
        super.viewWillAppear(animated)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


    // MARK: - Table View

    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return sections?.count ?? 0
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath)

        if let sections=sections
        {
            let section = sections[indexPath.row] as! String
            cell.textLabel!.text = section
        }
        else
        {
            cell.textLabel!.text = ""
        }
        return cell
    }

    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath)
    {
        selectScreen(index: indexPath.row)
    }
}

