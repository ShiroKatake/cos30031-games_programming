const prompter = require('discordjs-prompter');

//Command info, useful for the help command
module.exports.config = {
    name: 'addevent',
    usage: ['[Event Name]'],
    argLength: [1],
    argCheckOverride: true,
    shortcut: ['add'],
    description: 'Add an event into the event list.'
}

module.exports.run = async (message, commandArguments, Event) => {
    
    //Prompt the sender to enter a description for the event
    prompter.message(message.channel, {
        question: `Add a short description for your event ${commandArguments.map((a, i) => {return a}).join(' ')}!`,
        userId: message.author.id,
        max: 1,
        timeout: 60000,
    }).then(async response => {
        //If the sender takes longer than 60sec to write a description, send timed out message
        if (!response.size) {
            return message.reply(`response timed out...`);
        }

        //Else makes the response the description, and the addevent command's argument the event name
        const eventDescription = String(response.first());
        var eventName = commandArguments.join(' ');

        try {
            //If an event was deleted from the event list, it will leave a gap on the list
            //So when adding in new events, we need to check for potential gaps to fill in
            //                                                                            new event need to be inserted here
            //                                                                                             v
            //Eg. If event #3 was deleted from the event list, the list would look like this:        1, 2, 4, 5
            //If we convert the list into an array, the index numbers for them would look like this: 0, 1, 2, 3

            //A gap on the event list can be found by converting the list into an array, and find the first instance
            //where the eventID number on the list is not equal to the index number + 1 in the array

            //Because index numbers in arrays start at 0, and numbers on the event list start at 1,
            //we need to add 1 to each index number in order to compare it:
            // 0 + 1 == 1
            // 1 + 1 == 2
            // 2 + 1 != 4 (Gap found!)

            //findAll() will find all the events and convert them into an array
            let allEvents = await Event.findAll();

            //In case the list is empty, this will be the number on the list
            let numberOnTheList = 1;

            if (allEvents.length != 0) {
                //The callback function in find() will execute once for each element until the matching condition is true, then it would return the element
                //So for each element, if the eventID of the element does not equal its index + 1, return its index + 1
                let result = allEvents.find((element, index) => {
                    if (element.eventId != index + 1) {
                        console.log('Number missing on the list: ' + (index + 1));
                        return numberOnTheList = index + 1; //i + 1 is the number that it's meant to be on the list
                    }

                });
                if (result == null) {
                    numberOnTheList = allEvents.length + 1;
                }
                console.log(numberOnTheList);
            }
            console.log("Adding event...");
            let result = await Event.create({
                eventId: numberOnTheList,
                eventName: eventName,
                eventDescription: eventDescription,
                authorId: message.author.id
            });

            //Send confirm message
            console.log(`Event ${eventName} added.\nEvent description: ${eventDescription}`);
            return message.reply(`Event ${eventName} has been added to the list.`);
        }
        catch (e) {
            console.log(e);
            return message.reply(`Something went wrong with executing that command. ${e.name}`);
        }
    });
}