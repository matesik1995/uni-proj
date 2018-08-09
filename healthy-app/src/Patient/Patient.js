import React, { Component } from 'react';
import './Patient.css';
import Timeline from "../Timeline/Timeline"

class Patient extends Component {
    constructor(props) {
        super(props);
        this.state = {
            isFetched: false,
            collapsed: true
        };

        this.items = [];

        this.url = this.props.url;
        this.name = this.props.name;
        this.id = this.props.id;
        this.handleOnClick = this.handleOnClick.bind(this);
        this.fetchPatientDetails = this.fetchPatientDetails.bind(this);
    }

    fetchPatientDetails(url) {
        fetch(url + '/$everything')
            .then(blob => blob.json())
            .then(data => {
                this.items.push.apply(this.items, data.entry);
                data.link.forEach(e => {
                    if (e.relation === 'next') {
                        this.fetchPatientDetails(e.url)
                    }
                });
                this.setState({
                    isFetched: true,
                });
            })
            .catch(err => console.error(err));
    }

    handleOnClick(e) {
        if (!this.state.isFetched) {
            this.fetchPatientDetails(this.props.url);
        }
        console.log("this",this);
        this.setState({collapsed: !this.state.collapsed})
        this.forceUpdate();
    }

    render() {
        let info = this.items.filter(e => e.resource.resourceType === 'Patient')[0];
        return (
            <div className='patient'>
                <span className='name' onClick={this.handleOnClick}>{this.name} <i className='id'>({this.id})</i></span>
                <div className='info' style={{display:this.state.collapsed ? "none": "block"}}>
                    <ul>
                    {info && info.resource.name.family ? <li>Family name: {info.resource.name.family} {}</li> : ""}
                    {info && info.resource.address ? <li>Address: {info.resource.address[0].text}</li> : ""}
                    {info && info.resource.telecom ? <li>Contact: {info.resource.telecom[0].value}</li> : ""}
                    {info && info.resource.birthDate ? <li>Birth date: {info.resource.birthDate}</li> : ""}
                    {info && info.resource.gender ? <li>Gender: {info.resource.gender}</li> : ""}
                    {info && info.resource.maritalStatus ? <li>Marital status: {info.resource.maritalStatus}</li> : ""}
                    </ul> 
                </div>
                <div style={{display:this.state.collapsed ? "none": "block"}}><Timeline items={this.items} /></div>
            </div>
        );
    }
}

export default Patient;