const Discord = require('discord.js');
const {Sequelize} = require('sequelize');
const { Op } = require('sequelize');
const prompter = require('discordjs-prompter');

//Command info, useful for the help command
module.exports.config = {
    name: 'randomevent',
    usage: [''],
    argLength: [0],
    argCheckOverride: false,
    shortcut: ['rnd'],
    description: 'Pick a random event from the list (exclude last 2 picked events).'
}

module.exports.run = async (message, commandArguments, Event, PickedEvents) => {
    try {
        //Look up the PickedEvents database to get the last 2 picked events
        console.log('Looking for picked events...');
        let result = await PickedEvents.findAll({order: [['updatedAt', 'DESC']], attributes: ['eventId']});

        //If the database is empty, make the indices for the "last 2 events" 0. If not, assign the oldest as pickedEvent2 and earliest as pickedEvent1
        var {pickedEvent1, pickedEvent2} = (result.length == 0) ? {pickedEvent1: 0, pickedEvent2: 0} : {pickedEvent1: result[0].eventId, pickedEvent2: result[1].eventId};
        console.log(`Last 2 picked events (latest first): ${pickedEvent1}, ${pickedEvent2}`);

        //Find a random event from Event database while using pickedEvent1 and pickedEvent2 as filters to avoid choosing the last 2 events again
        const event = await Event.findOne({
            where: {
                eventId: {
                    [Op.and]: [
                        {[Op.ne]: pickedEvent1}, 
                        {[Op.ne]: pickedEvent2}
                    ]
                }
            }, 
            order: Sequelize.fn( 'RAND' ), 
            limit: 1 
        });

        //Find the event's author id
        const eventAuthor = await message.client.fetchUser(event.authorId);

        //Assign the event's name into a variable for later use
        const eventName = event.eventName;

        //Prepare an embedded message to send
        const eventListEmbed = new Discord.RichEmbed()
            .setColor('#7ec699')
            .setTitle('Random Event Picked!')
            .setFooter(`Added by ${eventAuthor.tag}`)
            .addField(`${event.eventId}. ` + event.eventName, event.eventDescription + '\n\nDo you want to pick this event for the fc?');
        console.log(`Event info for ${event.eventName}: ${event.eventDescription}`);

        //Also make it a reaction prompt for the sender to respond
        prompter.reaction(message.channel, {
            question: eventListEmbed, //Send the embedded message as the 'question' of the prompt
            timeout: 60000,
        })
        .then(async response => {
            //If the sender takes too long to react, send timed out message
            if (!response) return message.reply(`response timed out, event canceled...`);

            if (response === 'yes') {
                //Replace the oldest event (pickedEvent2) in the picked list with this event,
                //so this new event won't get picked the next 2 times
                console.log("Registering event...");
                let result = await PickedEvents.update({eventId: event.eventId}, {where: {eventId: pickedEvent2}});

                //Send confirm message
                console.log(`Event ${eventName} added to picked list.`);
                return message.reply(`You chose yes, event ${eventName} picked!`);
            }

            //If the sender replies no, cancel everything. 
            //The limitation of the discord-prompter package prevents continuing to look for the next random event from the same message impossible
            if (response === 'no') return message.channel.send(`You chose no, event ${eventName} canceled.`);
        });
    }
    catch (e) {
        console.log(e);
        return message.reply(`Something went wrong with executing that command. ${e.name}`);
    }
}